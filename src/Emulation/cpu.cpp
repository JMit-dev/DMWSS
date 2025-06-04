#include "Emulation/cpu.h"
#include "Util/log.h"

namespace dmwss::emu {

// -----------------------------------------------------------
//  very small opcode subset (NOP, JP nn) just so code runs
// -----------------------------------------------------------
void Cpu::reset() {
  af = 0x01B0;
  bc = 0x0013;
  de = 0x00D8;
  hl = 0x014D;
  sp = 0xFFFE;
  pc = 0x0100;
  ime = false;
}

int Cpu::step() {
  const u8 op = fetch8();

#ifdef DEBUG
  LOG_DEBUG("PC=%04X  OP=%02X", pc - 1, op);
#endif

  switch (op) {
  case 0x00: // NOP
    return 4;
  case 0xC3: { // JP nn
    pc = fetch16();
    return 16;
  }
  default:
#ifdef DEBUG
    LOG_WARN("Unimplemented opcode %02X", op);
#endif
    return 4; // act like NOP for now
  }
}

} // namespace dmwss::emu
