AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME twiteng
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE parse_tests.cpp addtweet_tests.cpp
)
