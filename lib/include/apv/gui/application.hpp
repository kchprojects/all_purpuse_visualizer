#pragma once
#include <apv/backends/backend_concept.hpp>
#include <apv/gui/menu.hpp>
#include <apv/utils/log.hpp>
#include <fmt/core.h>

namespace apv {
template <Backend B> class Application {
  B backend_;
  MenuBar main_menu_;

public:
  Application() = default;
  Application &set_main_menu(MenuBar main_menu) {
    main_menu_ = std::move(main_menu);
    return *this;
  }
  MenuBar &main_menu() { return main_menu_; }
  const MenuBar &main_menu() const { return main_menu_; }

  void init() {
    try {
      backend_.init_app();
    } catch (const std::exception &e) {
      auto message = fmt::format("Cannot initialize backend: {}.", e.what());
      log(log_t::error{message});
      throw std::runtime_error(message);
    }
  }
  void run() {
    while (backend_.is_alive()) {
      backend_.render_frame(*this);
    }
  }
};
} // namespace apv
