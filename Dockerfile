FROM ubuntu:18.04

RUN apt-get update --fix-missing

RUN apt-get install -y g++ cmake libgtest-dev google-mock lcov libsqlite3-dev clang-tidy-9

# Build and install Google Test and Google Mock
RUN cd /usr/src/googletest/googlemock && \
    cd build-aux && \
    cmake -j$(nproc) .. && \
    make -j$(nproc) && \
    make install

ARG YASA_ROOT_DIR=/usr/local/src/yasa

WORKDIR ${YASA_ROOT_DIR}
COPY . .

# Debug build with warnings, tests and code coverage
WORKDIR ${YASA_ROOT_DIR}/debug-build
RUN cmake \
        -j$(nproc) \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON /usr/lib/llvm-9/ \
        -DCMAKE_BUILD_TYPE=DEBUG .. && \
    ln -s $PWD/compile_commands.json /usr/lib/llvm-9/ && \
    clang-tidy-9 \
        ../src/*.cc \
        -quiet \
        -checks=cppcoreguidelines*,modernize-*,-modernize-use-trailing-return-type,misc-*,performance-*,readability-* && \
    make -j$(nproc) RunAllTests && \
    tests/RunAllTests && \
    lcov --capture --directory . --output-file coverage.info && \
    lcov --remove coverage.info \
        '/usr/include/*' \
        '/usr/local/include/*' \
        '/usr/local/src/yasa/tests/*' \
        --quiet --output-file coverage.info && \
    lcov --list coverage.info

# Build the program that is launched when `docker run yasa` is executed
WORKDIR ${YASA_ROOT_DIR}/release-build
RUN cmake -j$(nproc) -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc) yasa && \
    cd src && \
    make install && \
    yasa --version

WORKDIR /

ENTRYPOINT ["yasa"]
