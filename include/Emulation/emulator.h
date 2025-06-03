#ifndef EMULATOR_H
#define EMULATOR_H
#include "cpu.h"
#include "ppu.h"
#include "timer.h"

namespace dmwss::emu {

class Emulator {
public:
  explicit Emulator(const Cartridge &cart);

  /// Run enough cycles for one video frame (≈59.73 Hz)
  void frame();

  /// quick access for platform layer
  const std::array<u16, Ppu::LCD_W * Ppu::LCD_H> &framebuffer() const {
    return ppu.frame;
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
