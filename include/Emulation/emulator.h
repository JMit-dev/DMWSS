#ifndef EMULATOR_H
#define EMULATOR_H
#include "Emulation/cpu.h"
#include "Emulation/ppu.h"
#include "Emulation/timer.h"

namespace dmwss::emu {

class Emulator {
public:
  explicit Emulator(Cartridge &cart);

  /// Run enough cycles for one video frame (≈59.73 Hz)
  void frame();

  /// quick access for a platform layer (SDL, etc.)
  // ✱ use LCD_W/LCD_H directly (they’re in this namespace)
  // ✱ and return ppu_.frame, not ppu.frame
  const std::array<u16, LCD_W * LCD_H> &framebuffer() const {
    return ppu_.frame; // ✱
  }

  Cpu &cpu() { return cpu_; }
  Timer &timer() { return timer_; }
  Mmu &mmu() { return mmu_; }

private:
  Mmu mmu_;
  Cpu cpu_;
  Timer timer_;
  Ppu ppu_;
};

} // namespace dmwss::emu
#endif // EMULATOR_H
