#include <GL/glew.h> // Initialize with glewInit()
#include <apv/backends/imgui/imgui_backend.hpp>
#include <apv/utils/log.hpp>
#include <bindings/imgui_impl_glfw.h>
#include <bindings/imgui_impl_opengl3.h>
#include <fmt/core.h>
#include <imgui.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include <apv/gui/application.hpp>

namespace apv {
static void glfw_error_callback(int error, const char *description) {
  log(log_t::error{fmt::format("Glfw Error {}:{}", error, description)});
}
void ImguiBackend::init_app() {
  setup_main_window();
  setup_context();
}

void ImguiBackend::setup_main_window() {
  log(log_t::info{"Window init"});
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::string message = "Cannot initialize glfw";
    log(log_t::error{message});
    throw std::runtime_error(message);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only

  // Create window with graphics context
  main_window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
  if (!main_window) {
    std::string message = "Cannot initialize glfw window";
    log(log_t::error{message});
    throw std::runtime_error(message);
  }

  glfwMakeContextCurrent(main_window);
  glfwSwapInterval(1); // Enable vsync

  if (glewInit() != GLEW_OK) {
    std::string message = "Failed to initialize OpenGL loader!";
    log(log_t::error{message});
    throw std::runtime_error(message);
  }
}

void ImguiBackend::setup_context() {
  log(log_t::info{"Setup context"});
  const char *glsl_version = "#version 410";
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(main_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
}

bool ImguiBackend::is_alive() {
  glfwPollEvents();
  return !glfwWindowShouldClose(main_window);
}
void render_conan_logo() {
  ImDrawList *draw_list = ImGui::GetWindowDrawList();
  float sz = 300.0f;
  static ImVec4 col1 = ImVec4(68.0 / 255.0, 83.0 / 255.0, 89.0 / 255.0, 1.0f);
  static ImVec4 col2 = ImVec4(40.0 / 255.0, 60.0 / 255.0, 80.0 / 255.0, 1.0f);
  static ImVec4 col3 = ImVec4(50.0 / 255.0, 65.0 / 255.0, 82.0 / 255.0, 1.0f);
  static ImVec4 col4 = ImVec4(20.0 / 255.0, 40.0 / 255.0, 60.0 / 255.0, 1.0f);
  const ImVec2 p = ImGui::GetCursorScreenPos();
  float x = p.x + 4.0f, y = p.y + 4.0f;
  draw_list->AddQuadFilled(
      ImVec2(x, y + 0.25 * sz), ImVec2(x + 0.5 * sz, y + 0.5 * sz),
      ImVec2(x + sz, y + 0.25 * sz), ImVec2(x + 0.5 * sz, y), ImColor(col1));
  draw_list->AddQuadFilled(ImVec2(x, y + 0.25 * sz),
                           ImVec2(x + 0.5 * sz, y + 0.5 * sz),
                           ImVec2(x + 0.5 * sz, y + 1.0 * sz),
                           ImVec2(x, y + 0.75 * sz), ImColor(col2));
  draw_list->AddQuadFilled(ImVec2(x + 0.5 * sz, y + 0.5 * sz),
                           ImVec2(x + sz, y + 0.25 * sz),
                           ImVec2(x + sz, y + 0.75 * sz),
                           ImVec2(x + 0.5 * sz, y + 1.0 * sz), ImColor(col3));
  draw_list->AddLine(ImVec2(x + 0.75 * sz, y + 0.375 * sz),
                     ImVec2(x + 0.75 * sz, y + 0.875 * sz), ImColor(col4));
  draw_list->AddBezierCurve(ImVec2(x + 0.72 * sz, y + 0.24 * sz),
                            ImVec2(x + 0.68 * sz, y + 0.15 * sz),
                            ImVec2(x + 0.48 * sz, y + 0.13 * sz),
                            ImVec2(x + 0.39 * sz, y + 0.17 * sz), ImColor(col4),
                            10, 18);
  draw_list->AddBezierCurve(
      ImVec2(x + 0.39 * sz, y + 0.17 * sz), ImVec2(x + 0.2 * sz, y + 0.25 * sz),
      ImVec2(x + 0.3 * sz, y + 0.35 * sz), ImVec2(x + 0.49 * sz, y + 0.38 * sz),
      ImColor(col4), 10, 18);
}
static void HelpMarker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly)) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}
static void ShowDockingDisabledMessage() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
  ImGui::Text(
      "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
  ImGui::SameLine(0.0f, 0.0f);
  if (ImGui::SmallButton("click here"))
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

ImGuiWindowFlags get_main_window_flags() {
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  return window_flags;
}

ImGuiID
submit_dock(const std::string &dock_name,
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None) {
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGuiID dockspace_id;
  dockspace_id = ImGui::GetID(dock_name.c_str());
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  return dockspace_id;
}

void ImguiBackend::render_menu(const MenuBar &menu) {
  if (ImGui::BeginMenuBar()) {
    for (const MenuTab &menu_tab : menu) {
      if (ImGui::BeginMenu(menu_tab.label().c_str())) {
        ImGui::Separator();
        for (const MenuItem &menu_item : menu_tab.items()) {
          if (ImGui::MenuItem(menu_item.label().c_str(), "")) {
            menu_item.trigger();
          }
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
  }
}

void ImguiBackend::render_main_window(const MenuBar &main_menu) {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  if (ImGui::Begin("MainWindow", nullptr, get_main_window_flags())) {
    ImGui::PopStyleVar();
    submit_dock("MainDock");
    render_menu(main_menu);
  }
  ImGui::End();
}

void ImguiBackend::init_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImguiBackend::submit_frame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  int display_w, display_h;
  glfwGetFramebufferSize(main_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glfwSwapBuffers(main_window);
}

void ImguiBackend::render_example_windows() {
  if (ImGui::Begin("Win", nullptr)) {
  }
  ImGui::End();
  if (ImGui::Begin("Win2", nullptr)) {
  }
}
} // namespace apv
