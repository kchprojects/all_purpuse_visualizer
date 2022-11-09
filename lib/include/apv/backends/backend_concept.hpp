#include <concepts>
namespace apv
{
    template<typename T>
    concept Backend = requires(T a)
    {
        { a.init_app()};
        { a.create_window()};
    };
} // namespace apv
