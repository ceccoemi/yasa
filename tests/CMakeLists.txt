include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(GTest REQUIRED)  # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib gmock pthread gcov)

add_executable(SentimentTest SentimentTest.cc)
target_link_libraries(
	SentimentTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(SentimentTest SentimentTest.cc)

add_executable(SqliteHandlerTest SqliteHandlerTest.cc)
target_link_libraries(
	SqliteHandlerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(SqliteHandlerTest SqliteHandlerTest.cc)

add_executable(SqliteDictionaryTest SqliteDictionaryTest.cc)
target_link_libraries(
	SqliteDictionaryTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(SqliteDictionaryTest SqliteDictionaryTest.cc)

add_executable(PreprocessingTest preprocessingTest.cc)
target_link_libraries(
	PreprocessingTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(PreprocessingTest preprocessingTest.cc)

add_executable(TrainerTest TrainerTest.cc)
target_link_libraries(
	TrainerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(TrainerTest TrainerTest.cc)

add_executable(ClassifierTest ClassifierTest.cc)
target_link_libraries(
	ClassifierTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(ClassifierTest ClassifierTest.cc)

file(GLOB sourceFiles *.cc)
add_executable(RunAllTests ${sourceFiles})
target_link_libraries(
	RunAllTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
gtest_discover_tests(RunAllTests ${sourceFiles})
