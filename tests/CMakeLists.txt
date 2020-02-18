include_directories(${CMAKE_SOURCE_DIR}/src)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

find_package(GTest REQUIRED)  # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib gmock pthread gcov)

add_executable(sentimentTest SentimentTest.cc)
target_link_libraries(
	sentimentTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(sentimentTest SentimentTest.cc)

add_executable(SqliteHandlerTest SqliteHandlerTest.cc)
target_link_libraries(
	SqliteHandlerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(SqliteHandlerTest SqliteHandlerTest.cc)

add_executable(sqliteDictionaryTest SqliteDictionaryTest.cc)
target_link_libraries(
	sqliteDictionaryTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(sqliteDictionaryTest SqliteDictionaryTest.cc)

add_executable(fileProcessingTest fileProcessingTest.cc)
target_link_libraries(
	fileProcessingTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(fileProcessingTest fileProcessingTest.cc)

add_executable(trainerTest TrainerTest.cc MockDictionary.h)
target_link_libraries(
	trainerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(trainerTest TrainerTest.cc)

file(GLOB sourceFiles *.cc)
add_executable(runAllTests ${sourceFiles})
target_link_libraries(
	runAllTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(runAllTests ${sourceFiles})
