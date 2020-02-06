file(GLOB headerFiles *.h)
file(GLOB sourceFiles *.cc)
add_executable(yasa ${headerFiles} ${sourceFiles})
target_link_libraries(yasa gcov)

include(GNUInstallDirs)
install(
	TARGETS yasa
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

