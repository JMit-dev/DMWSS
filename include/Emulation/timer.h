#ifndef TIMER_H
#define TIMER_H
#include "Util/types.h"

namespace dmwss::emu {

struct Timer {
  // DIV increments at 16384 Hz (every 256 master cycles)
  u16 div = 0;
  u8 tima = 0, tma = 0, tac = 0;

  /// advance given machine cycles; returns true if TIMA overflowed
  bool tick(int cycles);
};
} // namespace dmwss::emu
#endif // TIMER_H
