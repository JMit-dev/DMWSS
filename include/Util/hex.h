#ifndef HEX_H
#define HEX_H
#include "Util/types.h"
#include <cstddef>
#include <cstdio>
#include <string_view>

namespace dmwss::util {

static inline bool printable(u8 c) { return c >= 32 && c <= 126; }

void hexDump(std::string_view tag, const u8 *d, std::size_t n, u16 base) {
  std::printf("--- %.*s (%zu B) ---\n", int(tag.size()), tag.data(), n);
  for (std::size_t i = 0; i < n; i += 16) {
    std::printf("%04X: ", base + static_cast<u16>(i));
    for (int j = 0; j < 16; ++j) {
      if (i + j < n)
        std::printf("%02X ", d[i + j]);
      else
        std::printf("   ");
    }
    std::printf(" ");
    for (int j = 0; j < 16 && i + j < n; ++j)
      std::printf("%c", printable(d[i + j]) ? d[i + j] : '.');
    std::printf("\n");
  }
}
} // namespace dmwss::util
#endif // HEX_H
