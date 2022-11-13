#include <apv/backends/imgui/imgui_backend.hpp>
#include <apv/gui/application.hpp>
#include <apv/gui/menu.hpp>

int main(int argc, char const *argv[]) {
  using namespace apv;
  Application<ImguiBackend> app;
  app.set_main_menu(
      {MenuTab("File", {},
               {MenuItem("Hello", []() { log_info("Hello there"); })}),
       MenuTab("Edit", {},
               {MenuItem("Undo", []() { log_info("Undo"); }),
                MenuItem("Redo", []() { log_info("Redo"); })})});
  app.init();
  app.run();
  return 0;
}
