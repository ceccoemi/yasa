FROM ubuntu:18.04

RUN apt-get update --fix-missing

RUN apt-get install -y g++ cmake libgtest-dev lcov

### Compile and install Google Test ###
RUN cd /usr/src/gtest && \
    cmake -j$(nproc) . && \
    make -j$(nproc) && \
    make install

WORKDIR /usr/local/src/yasa
COPY . .
RUN mkdir build && \
    cd build && \
    cmake -j$(nproc) .. && \
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
