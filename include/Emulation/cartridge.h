#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include "Util/types.h"
#include <string_view>
#include <vector>

namespace dmwss::emu {

struct Cartridge {
  explicit Cartridge(std::string_view path);

  u8 read(u16 addr) const;
  void write(u16 addr, u8 val);

  bool loaded() const { return !rom.empty(); }

private:
  std::vector<u8> rom;
  std::vector<u8> sram; // up to 32 KiB external RAM
                        // TODO: MBC mode registers, RTC, etc.
};
} // namespace dmwss::emu
#endif // CARTRIDGE_H
