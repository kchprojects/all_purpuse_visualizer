mkdir build && cd build
conan install ..
cmake ..
make -j8