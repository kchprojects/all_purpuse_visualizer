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
  void render_frame();
  void destroy();

private:
  void render_main_window();
  void setup_main_window();
  void setup_context();
};
} // namespace apv
