#ifndef STATE_H
#define STATE_H
#include "Emulation/cpu.h"
#include "Emulation/mmu.h"
#include <cstdio>

namespace dmwss::dbg {

void printState(const emu::Cpu &c, const emu::Mmu &m) {
  using namespace emu;
  std::printf("AF=%04X BC=%04X DE=%04X HL=%04X SP=%04X PC=%04X  ", c.af, c.bc,
              c.de, c.hl, c.sp, c.pc);
  const u8 tima = m.rd8(0xFF05);
  const u8 div = m.rd8(0xFF04);
  const u8 ly = m.rd8(0xFF44);
  std::printf("DIV=%02X TIMA=%02X LY=%02X\n", div, tima, ly);
}
} // namespace dmwss::dbg

#ifdef DEBUG
#define DEBUG_STATE(cpu, mmu) ::dmwss::dbg::printState(cpu, mmu)
#else
#define DEBUG_STATE(cpu, mmu) ((void)0)
#endif
#endif // STATE_H
