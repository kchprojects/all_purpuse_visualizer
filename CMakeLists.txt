cmake_minimum_required(VERSION 3.20)
project(apv)

option(USE_CONAN "Use conan package manager" ON)

if (USE_CONAN)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )  # Includes the contents of the conanbuildinfo.cmake file.
	conan_basic_setup()  # Prepares the CMakeList.txt for Conan.
endif (USE_CONAN)

add_subdirectory(lib)
add_subdirectory(apps)