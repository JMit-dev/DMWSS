#include "Emulation/cartridge.h"
#include <fstream>
#include <iterator>

namespace dmwss::emu {

Cartridge::Cartridge(std::string_view path) {
  std::ifstream f(path.data(), std::ios::binary);
  if (!f)
    return; // leave rom empty → loaded() == false
  rom.assign(std::istreambuf_iterator<char>(f),
             std::istreambuf_iterator<char>());
  sram.resize(32 * 1024, 0xFF); // reserve 32 KiB ext-RAM (DMG limit)
}

// 0000–7FFF  = ROM (banked later)
// A000–BFFF  = external RAM (if present)
u8 Cartridge::read(u16 a) const {
  if (a < rom.size())
    return rom[a];
  if (a >= 0xA000 && a <= 0xBFFF && !sram.empty())
    return sram[a - 0xA000];
  return 0xFF;
}

void Cartridge::write(u16 a, u8 v) {
  if (a >= 0xA000 && a <= 0xBFFF && !sram.empty())
    sram[a - 0xA000] = v;
  // MBC control registers will live here later
}

} // namespace dmwss::emu
