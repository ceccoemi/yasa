set(
	CMAKE_CXX_CLANG_TIDY
	clang-tidy-9
    -checks=cppcoreguidelines*,modernize-*,-modernize-use-trailing-return-type,misc-*,performance-*,readability-*
)

file(GLOB headerFiles *.h)
file(GLOB sourceFiles *.cc)
list(REMOVE_ITEM sourceFiles ${CMAKE_CURRENT_LIST_DIR}/main.cc)

add_library(yasalib ${headerFiles} ${sourceFiles})
target_link_libraries(
	yasalib
	PUBLIC sqlite3
	PUBLIC stdc++fs  # for std::experimental::filesystem
	PRIVATE gcov
)

add_executable(yasa main.cc)
target_link_libraries(yasa yasalib ${CONAN_LIBS})

include(GNUInstallDirs)  # import CMAKE_INSTALL_BINDIR
install(TARGETS yasa RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
