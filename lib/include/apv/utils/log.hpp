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
} // namespace log_t

extern std::shared_ptr<spdlog::logger> default_logger;

template <typename T> concept Logger = requires(T a) {
  {a.error(std::string{})};
  {a.warn(std::string{})};
};

template <Logger L> void log(log_t::warn w, L &l) { l.warn(w.message); }
inline void log(log_t::warn w) { log(w, *default_logger); }

template <Logger L> void log(log_t::error e, L &l) { l.error(e.message); }
inline void log(log_t::error e) { log(e, *default_logger); }
} // namespace apv
