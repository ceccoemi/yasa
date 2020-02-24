include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(GTest REQUIRED)  # import GTEST_BOTH_LIBRARIES

set(TEST_LIB yasalib gmock pthread gcov ${CONAN_LIBS})

add_executable(SentimentTest SentimentTest.cc)
target_link_libraries(
	SentimentTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

add_executable(SqliteHandlerTest SqliteHandlerTest.cc)
target_link_libraries(
	SqliteHandlerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

add_executable(SqliteDictionaryTest SqliteDictionaryTest.cc)
target_link_libraries(
	SqliteDictionaryTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

add_executable(PreprocessingTest preprocessingTest.cc)
target_link_libraries(
	PreprocessingTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

add_executable(TrainerTest TrainerTest.cc)
target_link_libraries(
	TrainerTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

add_executable(ClassifierTest ClassifierTest.cc)
target_link_libraries(
	ClassifierTest ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)

file(GLOB sourceFiles *.cc)
add_executable(RunAllTests ${sourceFiles})
target_link_libraries(
	RunAllTests ${GTEST_BOTH_LIBRARIES} ${TEST_LIB}
)
