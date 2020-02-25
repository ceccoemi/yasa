#!/bin/sh

set -o errexit
set -o nounset

if [ ! -e ~/.conan/profiles/default ]; then
    # Generates default profile detecting GCC and sets old ABI
    conan profile new default --detect
    # Sets libcxx to C++11 ABI
    conan profile update settings.compiler.libcxx=libstdc++11 default
fi

if [ -e ./build ]; then
    rm -rf ./build;
fi

mkdir build && cd build
conan install ..

cmake -j$(nproc) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

make -j$(nproc) RunAllTests

bin/RunAllTests

lcov --capture --directory . --output-file coverage.info
#lcov --remove coverage.info \
#        '/usr/include/*' \
#        '/usr/local/include/*' \
#        '/usr/local/src/yasa/tests/*' \
#        --quiet --output-file coverage.info
lcov --list coverage.info

exit 0

