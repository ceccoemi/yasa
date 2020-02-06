file(GLOB headerFiles *.h)
file(GLOB sourceFiles *.cc)

add_library(yasalib ${headerFiles} ${sourceFiles})
target_link_libraries(yasalib gcov sqlite3)

add_executable(yasa main.cc)
target_link_libraries(yasa yasalib)

include(GNUInstallDirs)
install(
	TARGETS yasa
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

