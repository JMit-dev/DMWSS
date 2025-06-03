#ifndef PPU_H
#define PPU_H
#include "Util/types.h"
#include <array>

namespace dmwss::emu {

constexpr int LCD_W = 160;
constexpr int LCD_H = 144;

struct Ppu {
  /// RGB555 framebuffer for CGB; DMG uses lower 2 bits of each component
  std::array<u16, LCD_W * LCD_H> frame{};

  void reset();
  /// advance by <cycles>; raise V-Blank interrupt when a frame ends
  bool tick(int cycles); // returns true on V-Blank
private:
  int dotCounter = 0; // 0-456 per scanline
  int line = 0;       // 0-153
                      // TODO: LCDC, STAT, palettes, FIFOs…
};
} // namespace dmwss::emu
#endif // TIMER_H
