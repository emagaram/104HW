AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME search
	USER_SOURCE ${DIR_SOURCES} #${HW_DIR}/twiteng.cpp ${HW_DIR}/user.cpp ${HW_DIR}/tweet.cpp ${HW_DIR}/util.cpp ${HW_DIR}/datetime.cpp
	TEST_SOURCE search_tests.cpp
	RUNTIME_TEST_SOURCE runtime_tests.cpp)
