#include "Emulation/emulator.h"

namespace dmwss::emu {

Emulator::Emulator(Cartridge &cart) {
  mmu_.attach(&cart);
  cpu_.bus = &mmu_;
  cpu_.reset();
  timer_.div = 0;
  ppu_.reset();
}

/// run one 59.7 Hz video frame (≈ 70224 cycles on DMG)
void Emulator::frame() {
  int cycles = 0;
  while (cycles < CYCLES_PER_FRAME) {
    const int stepCycles = cpu_.step();
    if (timer_.tick(stepCycles)) {
      // TODO: set IF bit 2 (timer interrupt)
    }
    if (ppu_.tick(stepCycles)) {
      // TODO: set IF bit 0 (V-Blank interrupt)
    }
    cycles += stepCycles;
  }
}

} // namespace dmwss::emu
