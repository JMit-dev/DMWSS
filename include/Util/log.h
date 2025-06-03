#ifndef LOG_H
#define LOG_H
#include <cstdarg>
#include <cstdio>

namespace util {
enum class Level { Debug, Info, Warn, Error };

inline const char *tag(Level l) {
  switch (l) {
  case Level::Debug:
    return "\033[36m[DEBUG]\033[0m ";
  case Level::Info:
    return "\033[32m[INFO ]\033[0m ";
  case Level::Warn:
    return "\033[33m[WARN ]\033[0m ";
  case Level::Error:
    return "\033[31m[ERROR]\033[0m ";
  }
  return "";
}

inline void log(Level lvl, const char *fmt, ...) {
#ifdef DEBUG
  std::va_list ap;
  va_start(ap, fmt);
  std::fputs(tag(lvl), stdout);
  std::vfprintf(stdout, fmt, ap);
  std::fputc('\n', stdout);
  va_end(ap);
#else
  (void)lvl;
  (void)fmt; // avoid “unused” warnings in release
#endif
}
} // namespace util

#define LOG_DEBUG(...) ::util::log(::util::Level::Debug, __VA_ARGS__)
#define LOG_INFO(...) ::util::log(::util::Level::Info, __VA_ARGS__)
#define LOG_WARN(...) ::util::log(::util::Level::Warn, __VA_ARGS__)
#define LOG_ERROR(...) ::util::log(::util::Level::Error, __VA_ARGS__)
#endif // LOG_H
