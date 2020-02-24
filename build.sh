#!/usr/bin/sh

set -o errexit
set -o nounset

if [ ! -e ~/.conan/profiles/default ]; then
    # Generates default profile detecting GCC and sets old ABI
    conan profile new default --detect
    # Sets libcxx to C++11 ABI
    conan profile update settings.compiler.libcxx=libstdc++11 default
fi

if [ ! -e ./build ]; then
    mkdir build;
else
    echo "Directory ./build already exists.";
    exit 1;
fi

cd build
conan install ..

cmake .. -G "Unix Makefiles"
cmake --build .

./bin/RunAllTests

exit 0

