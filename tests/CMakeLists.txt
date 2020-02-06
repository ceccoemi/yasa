include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(GTest REQUIRED)  # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib pthread gcov)

add_executable(sentimentTest SentimentTest.cc)
target_link_libraries(
	sentimentTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(sentimentTest ${sourceFiles})

file(GLOB sourceFiles *.cc)
add_executable(runAllTests ${sourceFiles})
target_link_libraries(
	runAllTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(runAllTests ${sourceFiles})
