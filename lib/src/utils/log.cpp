#include <apv/utils/log.hpp>
namespace apv
{
    std::shared_ptr<spdlog::logger> default_logger = spdlog::stdout_color_mt("apv"); 
} // namespace apv
