CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -ggdb
COMPILE_OBJ = $(CXX) $(CXXFLAGS) -c
COMPILE_EXE = $(CXX) $(CXXFLAGS)

GTEST_LIB_PATH = ../../googletest/build/lib
GTEST_MAIN = $(GTEST_LIB_PATH)/libgtest_main.a
GTEST_CORE = $(GTEST_LIB_PATH)/libgtest.a
GTEST_INCLUDE = -I ../../googletest/googletest/include/ #location of gtest on my comp outside vm
EXE = .exe


#	GTEST_MAIN = -l gtest_main
#	GTEST_CORE = -l gtest
#	GTEST_INCLUDE = -I /usr/include/gtest/
#	EXE = 


all: tests_gtest$(EXE)


# $@ rule name
# $^ dependency name.

tests_gtest$(EXE) : tests_gtest.o #.o files here
	$(COMPILE_EXE) -pthread $(GTEST_INCLUDE) $(GTEST_MAIN) $(GTEST_CORE) $^ -o $@

# $<, first dependency, .cpp file first.
# $@, name of the rule. 

#file.o: file.cpp file.h
#	$(COMPILE_OBJ) $< -o $@

tests_gtest.o :tests_gtest.cpp
	$(COMPILE_OBJ) $(GTEST_INCLUDE) $< -o $@

.PHONY: clean

clean:
	$(RM) *.o
	$(RM) *.d	
	$(RM) *.exe