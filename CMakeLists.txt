cmake_minimum_required(VERSION 3.10.2)

project(
  yasa
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")

add_subdirectory(src)
add_subdirectory(tests)
