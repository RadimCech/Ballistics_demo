# Run these commands to install with conan:

conan install . --build=missing

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

cmake --build .

ctest --output-on-failure

./ballistics