#ifndef CMDLINE_H
#define CMDLINE_H
#include <filesystem>
#include <iostream>
#include <string_view>

namespace dmwss::util {

namespace fs = std::filesystem;

struct Options {
  fs::path romPath; // absolute path after parsing
  bool headless = false;
};

inline bool isFlag(std::string_view arg, std::string_view longOpt,
                   char shortOpt = '\0') {
  return arg == longOpt ||
         (shortOpt && arg.size() == 2 && arg[0] == '-' && arg[1] == shortOpt);
}

inline void printUsage(std::string_view prog) {
  std::cout << "Usage: " << prog
            << " [--rom <file>|-r <file>] [--headless] [--help|-h]\n"
               "  --rom, -r   Relative or absolute path to a .gb/.gbc file\n"
               "  --headless  Run without SDL output (debug/CI)\n";
}

inline bool parseArgs(int argc, char **argv, Options &out) {
  if (argc <= 1) {
    printUsage(argv[0]);
    return false;
  }

  for (int i = 1; i < argc; ++i) {
    std::string_view arg = argv[i];

    if (isFlag(arg, "--help", 'h')) {
      printUsage(argv[0]);
      return false;
    } else if (isFlag(arg, "--headless", '\0')) {
      out.headless = true;
    } else if (isFlag(arg, "--rom", 'r')) {
      if (i + 1 >= argc) {
        std::cerr << "Missing path after " << arg << "\n";
        return false;
      }
      out.romPath = fs::absolute(argv[++i]);
    } else { // bare argument → treat as ROM path
      out.romPath = fs::absolute(arg);
    }
  }

  // Sanity checks
  if (out.romPath.empty()) {
    std::cerr << "No ROM file specified\n";
    printUsage(argv[0]);
    return false;
  }
  if (!fs::exists(out.romPath)) {
    std::cerr << "ROM not found: " << out.romPath << "\n";
    return false;
  }
  return true;
}

} // namespace dmwss::util
#endif // CMDLINE_H
