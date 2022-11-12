cmake_minimum_required(VERSION 3.20)

project(apv_lib VERSION 0.0.1)

# add build dir to include conan find_lib
set(OLD_CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/..)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# cleanup module path change
set(CMAKE_MODULE_PATH ${OLD_CMAKE_MODULE_PATH})

file(GLOB_RECURSE SOURCES *.cpp)
set(IMGUI_BACKEND_SOURCES ../third_party/bindings/imgui_impl_glfw.cpp ../third_party/bindings/imgui_impl_opengl3.cpp)

message("${imgui_BUILD_MODULES_PATHS}") 

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC include ../third_party)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${IMGUI_BACKEND_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt spdlog::spdlog imgui::imgui GLEW::GLEW glfw::glfw)
