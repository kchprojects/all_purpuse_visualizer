cmake_minimum_required(VERSION 3.20)

project(apv_test VERSION 0.0.1)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE apv_test.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PUBLIC apv_lib)




