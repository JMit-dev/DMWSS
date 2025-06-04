#include "Emulation/ppu.h"

namespace dmwss::emu {

void Ppu::reset() {
  dotCounter = 0;
  line = 0;
  frame.fill(0);
}

// very coarse timing model: 456 dots per line, 154 lines per frame
bool Ppu::tick(int cycles) {
  dotCounter += cycles;
  if (dotCounter >= 456) {
    dotCounter -= 456;
    if (++line == 144) { // enter V-Blank
      return true;
    }
    if (line == 154) { // restart frame
      line = 0;
    }
  }
  return false;
}

} // namespace dmwss::emu
