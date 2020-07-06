AUX_SOURCE_DIRECTORY(${HW_DIR} SRC_DIR)

add_source_problem(
	NAME handlers
	USER_SOURCE ${SRC_DIR} #${HW_DIR}/twiteng.cpp ${HW_DIR}/user.cpp ${HW_DIR}/util.cpp ${HW_DIR}/datetime.cpp ${HW_DIR}/cmdhandler.cpp ${HW_DIR}/handler.cpp ${HW_DIR}/tweet.cpp
	TEST_SOURCE handler_tests.cpp)
