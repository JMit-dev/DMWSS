#include "Emulation/cartridge.h"
#include "Emulation/emulator.h"
#include "Util/cmdline.h"

#ifdef DEBUG
#include "Util/state.h"
#endif

#include <iostream>

int main(int argc, char **argv) {
  using namespace dmwss;

  util::Options opt;
  if (!util::parseArgs(argc, argv, opt))
    return 1;

  emu::Cartridge cart(opt.romPath.string());
  if (!cart.loaded()) {
    std::cerr << "Failed to load ROM: " << opt.romPath << "\n";
    return 1;
  }

  emu::Emulator gb(cart);

  std::cout << "DMWSS – running " << opt.romPath << "\n";

  while (true) {
    gb.frame();

#ifdef DEBUG // live register dump every frame
    dmwss::dbg::printState(gb.cpu(), gb.mmu());
#endif
    // TODO: break conditions, SDL pump, etc.
  }
  return 0;
}
