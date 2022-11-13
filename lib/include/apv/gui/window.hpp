#pragma once
#include <apv/backends/backend_concept.hpp>
namespace apv
{
    template<Backend B>
    class Window{
        B& backend_;
    public:
        Window(B& backend_){
            
        }
    };
} // namespace apv
