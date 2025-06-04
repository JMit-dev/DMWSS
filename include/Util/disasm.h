#ifndef DISASM_H
#define DISASM_H
#include "Emulation/mmu.h"
#include <cstdio>

namespace dmwss::dbg {
using emu::u16;
using emu::u8;

static const char *reg8[8] = {"B", "C", "D", "E", "H", "L", "(HL)", "A"};

static u16 one(const emu::Mmu &m, u16 pc) {
  u8 op = m.rd8(pc++);
  if (op == 0x00) {
    std::printf("%04X  NOP\n", pc - 1);
    return pc;
  }
  if (op == 0xC3) {
    u16 dst = m.rd8(pc) | m.rd8(pc + 1) << 8;
    std::printf("%04X  JP  $%04X\n", pc - 1, dst);
    return pc + 2;
  }
  if ((op & 0xC0) == 0x40) { // LD r,r
    std::printf("%04X  LD  %s,%s\n", pc - 1, reg8[(op >> 3) & 7], reg8[op & 7]);
    return pc;
  }
  std::printf("%04X  DB  %02X\n", pc - 1, op);
  return pc; // size 1 default
}

void disasm(const emu::Mmu &m, u16 pc, int n) {
  for (int i = 0; i < n; ++i)
    pc = one(m, pc);
}
} // namespace dmwss::dbg

#endif // DISASM_H
