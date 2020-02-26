include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(GTest REQUIRED) # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib pthread gcov)

file(GLOB sourceFiles *.cc)
add_executable(RunAllIntegrationTests ${sourceFiles})
target_link_libraries(RunAllIntegrationTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB})
