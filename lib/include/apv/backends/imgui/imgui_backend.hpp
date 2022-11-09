#include <source_location>
namespace apv
{
    class ImguiBackend{
    public:
        void init_app(){throw std::runtime_error(std::source_location::current().function_name());}
        bool create_window(){throw std::runtime_error(std::source_location::current().function_name());}
    };
} // namespace apv
