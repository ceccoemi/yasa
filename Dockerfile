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
    clang-tidy-9 ../src/*.cc -checks=*,-fuchsia-default-arguments-calls,-modernize-use-trailing-return-type,-llvm-header-guard -header-filter=.* && \
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
