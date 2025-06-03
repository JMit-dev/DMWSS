#ifndef CPU_H
#define CPU_H
#include "Util/types.h"
#include "mmu.h"

namespace dmwss::emu {

// Fixed clocks for DMG model; doubled on CGB (8.388 MHz master)
constexpr int MASTER_FREQ = 4'194'304;  // Hz
constexpr int CYCLES_PER_FRAME = 70224; // 154 × 456 dots

struct Cpu {
  // --- registers are packed for cache friendliness
  union {
    struct {
      u8 f, a;
    };
    u16 af;
  };
  union {
    struct {
      u8 c, b;
    };
    u16 bc;
  };
  union {
    struct {
      u8 e, d;
    };
    u16 de;
  };
  union {
    struct {
      u8 l, h;
    };
    u16 hl;
  };
  u16 sp{}, pc{};

  Mmu *bus = nullptr;

  void reset();
  /// execute ONE opcode, return machine cycles consumed
  int step();
  /// interrupt flag latch (IF register lives in MMU)
  bool ime = false;

private:
  u8 fetch8() { return bus->rd8(pc++); }
  u16 fetch16() {
    u16 v = bus->rd16(pc);
    pc += 2;
    return v;
  }
};
} // namespace dmwss::emu
#endif // CPU_H
