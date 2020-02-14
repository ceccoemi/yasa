FROM ubuntu:18.04

RUN apt-get update --fix-missing

RUN apt-get install -y g++ cmake libgtest-dev lcov libsqlite3-dev clang-tidy-9

### Compile and install Google Test ###
RUN cd /usr/src/gtest && \
    cmake -j$(nproc) . && \
    make -j$(nproc) && \
    make install

WORKDIR /usr/local/src/yasa
COPY . .
RUN mkdir build && \
    cd build && \
    cmake -j$(nproc) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON /usr/lib/llvm-9/ .. && \
    ln -s $PWD/compile_commands.json /usr/lib/llvm-9/ && \
    clang-tidy-9 ../src/*.cc \
        -checks=*,\
-cppcoreguidelines-owning-memory,\
-cppcoreguidelines-avoid-c-arrays,\
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
-cppcoreguidelines-pro-bounds-pointer-arithmetic,\
-fuchsia-statically-constructed-objects,\
-fuchsia-default-arguments-calls,\
-hicpp-no-array-decay,\
-hicpp-avoid-c-arrays,\
-modernize-avoid-c-arrays,\
-modernize-use-trailing-return-type,\
-llvm-header-guard,\
-cert-err58-cpp\
    -header-filter=.* \
    -line-filter='[{"name":"../src/ArgumentParser.cc","lines":[[35,35],[44,44]]}]' && \
    make -j$(nproc) && \
    tests/runAllTests && \
    src/yasa && \
    lcov --capture --directory . --output-file coverage.info && \
    lcov --remove coverage.info \
        '/usr/include/*' \
        '/usr/local/include/*' \
        '/usr/local/src/yasa/tests/*' \
        --quiet --output-file coverage.info && \
    lcov --list coverage.info && \
    make install

CMD ["yasa"]
