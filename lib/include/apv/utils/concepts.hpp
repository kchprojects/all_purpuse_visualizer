#pragma once
#include <concepts>
#include <string>

namespace apv {

template<typename T>
concept Triggerable = requires (T a) {
    a.trigger();
};

template<typename T> 
concept Hoverable = requires(T a){
  a.hover();
};

template<typename T>
concept WithLabel = requires(T a) {
  std::string(a.label());
};
} // namespace apv