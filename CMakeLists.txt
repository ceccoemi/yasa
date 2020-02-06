cmake_minimum_required(VERSION 3.10.2)

project(yasa VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra --coverage)

add_subdirectory(src)
add_subdirectory(tests)
