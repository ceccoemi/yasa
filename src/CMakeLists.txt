file(GLOB headerFiles *.h)
file(GLOB sourceFiles *.cc)

add_executable(yasa ${headerFiles} ${sourceFiles})
target_link_libraries(yasa gcov)

add_library(yasalib ${headerFiles} ${sourceFiles})

include(GNUInstallDirs)
install(
	TARGETS yasa
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

