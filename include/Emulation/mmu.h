#ifndef MMU_H
#define MMU_H
#include "Emulation/cartridge.h"
#include "Util/types.h"
#include <array>

namespace dmwss::emu {

class Mmu {
public:
  void attach(Cartridge *cart) { cart_ = cart; }

  u8 rd8(u16 addr) const;
  u16 rd16(u16 addr) const;
  void wr8(u16 addr, u8 data);
  void wr16(u16 addr, u16 data);

  auto &raw() { return ram_; } // fast path for DMA

private:
  std::array<u8, 0x2000> vram_{}; // 8 KiB
  std::array<u8, 0x2000> wram_{}; // 8 KiB
  std::array<u8, 0xA0> oam_{};    // sprite attr
  std::array<u8, 0x7F> hram_{};   // high RAM
  u8 ie_{};                       // interrupt enable
  Cartridge *cart_ = nullptr;
  std::array<u8, 0x10000> ram_{}; // flat mirror (simplest start)
};
} // namespace dmwss::emu
#endif // MMU_H
