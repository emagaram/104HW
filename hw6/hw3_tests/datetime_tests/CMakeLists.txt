AUX_SOURCE_DIRECTORY(${HW_DIR} DIR_SOURCES)

add_source_problem(
	NAME datetime
	USER_SOURCE ${DIR_SOURCES} 
	TEST_SOURCE comparator_tests.cpp constructor_tests.cpp istream_tests.cpp ostream_tests.cpp
)
