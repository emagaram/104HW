AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME user
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE constructor_tests.cpp feed_tests.cpp follower_tests.cpp following_tests.cpp tweets_tests.cpp)
