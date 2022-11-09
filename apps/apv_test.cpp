#include <apv/gui/application.hpp>
#include <apv/backends/imgui/imgui_backend.hpp>


int main(int argc, char const *argv[])
{
    using namespace apv;
    Application<ImguiBackend> app;
    app.init();
    return 0;
}
