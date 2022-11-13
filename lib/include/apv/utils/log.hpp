#pragma once
#include "spdlog/sinks/stdout_color_sinks.h"
#include <concepts>
#include <spdlog/spdlog.h>

#include <string>

namespace apv {
namespace log_t {
struct warn {
  std::string message;
};
struct error {
  std::string message;
};
struct debug {
  std::string message;
};
struct info {
  std::string message;
};
} // namespace log_t

extern std::shared_ptr<spdlog::logger> default_logger;

template <typename T> concept Logger = requires(T a) {
  {a.error(std::string{})};
  {a.warn(std::string{})};
};

template <Logger L> void log(log_t::warn w, L &l) { l.warn(w.message); }
template <Logger L> void log(log_t::error e, L &l) { l.error(e.message); }
template <Logger L> void log(log_t::debug d, L &l) { l.debug(d.message); }
template <Logger L> void log(log_t::info d, L &l) { l.info(d.message); }

template <typename LogType>
inline void log(LogType d) { log(d, *default_logger); }
} // namespace apv
