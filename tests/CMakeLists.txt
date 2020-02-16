include_directories(${CMAKE_SOURCE_DIR}/src)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

find_package(GTest REQUIRED)  # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib pthread gcov)

add_executable(sentimentTest SentimentTest.cc)
target_link_libraries(
	sentimentTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(sentimentTest SentimentTest.cc)

add_executable(sqliteHandleTest SqliteHandleTest.cc)
target_link_libraries(
	sqliteHandleTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(sqliteHandleTest SqliteHandleTest.cc)

add_executable(dictionaryTest DictionaryTest.cc)
target_link_libraries(
	dictionaryTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(dictionaryTest DictionaryTest.cc)

add_executable(fileProcessingTest fileProcessingTest.cc)
target_link_libraries(
	fileProcessingTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(fileProcessingTest fileProcessingTest.cc)

file(GLOB sourceFiles *.cc)
add_executable(runAllTests ${sourceFiles})
target_link_libraries(
	runAllTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(runAllTests ${sourceFiles})
