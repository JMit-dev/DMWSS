#include "Emulation/timer.h"

namespace dmwss::emu {

bool Timer::tick(int cycles) {
  div += cycles; // 16-bit wrap-around is fine
  if (!(tac & 0x04))
    return false; // disabled

  static const int rate[4] = {256, 4, 16, 64};
  static int acc = 0;

  acc += cycles;
  const int period = rate[tac & 0x03];

  bool overflow = false;
  while (acc >= period) {
    acc -= period;
    if (++tima == 0) {
      tima = tma;
      overflow = true;
    }
  }
  return overflow;
}

} // namespace dmwss::emu
