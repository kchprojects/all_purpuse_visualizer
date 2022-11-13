#pragma once
#include <apv/backends/backend_concept.hpp>
#include <apv/gui/menu.hpp>
#include <source_location>
#include <stdexcept>

struct GLFWwindow;
namespace apv {

class ImguiBackend {
  GLFWwindow *main_window;

public:
  void init_app();
  bool is_alive();
  bool create_window() {
    throw std::runtime_error(std::source_location::current().function_name());
  }
  template <typename T> void render_frame(T &app) {
    init_frame();
    static bool p_open = true;
    render_main_window(app.main_menu());
    render_example_windows();
    submit_frame();
  }
  void destroy();

private:
  void render_main_window(const MenuBar &main_menu);
  void render_menu(const MenuBar &main_menu);
  void setup_main_window();
  void setup_context();
  void submit_frame();
  void init_frame();

  void render_example_windows();
};
} // namespace apv
