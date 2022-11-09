#include <apv/backends/backend_concept.hpp>
#include <apv/utils/log.hpp>
#include <fmt/core.h>

namespace apv
{
    template<Backend B>
    class Application{
        B backend_;
    public:
        Application()=default;

        void init(){
            try
            {
                backend_.init_app();
            }
            catch(const std::exception& e)
            {
                auto message = fmt::format("Cannot initialize backend: {}.", e.what());
                log(log_t::error{message});
                throw std::runtime_error(message);
            }
        }
    };
} // namespace apv
