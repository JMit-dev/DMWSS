#include "Emulation/mmu.h"

namespace dmwss::emu {

static constexpr u16 VRAM_BASE = 0x8000;
static constexpr u16 WRAM0_BASE = 0xC000;

// ----------------- 8-bit -----------------
u8 Mmu::rd8(u16 a) const {
  if (a < 0x8000) // Cartridge ROM
    return cart_ ? cart_->read(a) : 0xFF;
  if (a >= VRAM_BASE && a < VRAM_BASE + 0x2000)
    return vram_[a & 0x1FFF];
  if (a >= WRAM0_BASE && a < WRAM0_BASE + 0x2000)
    return wram_[a & 0x1FFF];
  if (a >= 0xFE00 && a < 0xFEA0) // OAM
    return oam_[a & 0x9F];
  if (a >= 0xFF80 && a < 0xFFFF) // HRAM
    return hram_[a & 0x7F];
  if (a == 0xFFFF) // IE
    return ie_;
  return 0xFF; // I/O not yet implemented
}

void Mmu::wr8(u16 a, u8 v) {
  if (a < 0x8000) { // MBC / ROM writes
    if (cart_)
      cart_->write(a, v);
    return;
  }
  if (a >= VRAM_BASE && a < VRAM_BASE + 0x2000)
    vram_[a & 0x1FFF] = v;
  else if (a >= WRAM0_BASE && a < WRAM0_BASE + 0x2000)
    wram_[a & 0x1FFF] = v;
  else if (a >= 0xFE00 && a < 0xFEA0)
    oam_[a & 0x9F] = v;
  else if (a >= 0xFF80 && a < 0xFFFF)
    hram_[a & 0x7F] = v;
  else if (a == 0xFFFF)
    ie_ = v;
  // Other I/O ignored for now
}

// ----------------- 16-bit helpers -----------------
u16 Mmu::rd16(u16 a) const { return rd8(a) | (rd8(a + 1) << 8); }

void Mmu::wr16(u16 a, u16 v) {
  wr8(a, static_cast<u8>(v & 0xFF));
  wr8(a + 1, static_cast<u8>(v >> 8));
}

} // namespace dmwss::emu
