#AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

##Add other files with main methods in them
#list(REMOVE_ITEM DIR_SOURCES "${HW_DIR}/sat_solver.cpp")
#list(REMOVE_ITEM DIR_SOURCES "${HW_DIR}/sentences.cpp")

#add_executable_problem(
#	NAME scc
#	USER_SOURCE ${DIR_SOURCES}
#	TEST_SOURCE scc_tests.cpp
#	)
      add_makefile_problem(
	NAME scc
	MAKE_TARGET twitter
	EXECUTABLE_NAME twitter
	TEST_SOURCE scc_tests.cpp)
