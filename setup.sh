mkdir -p build && cd build
conan install ..
cmake ..
make -j8