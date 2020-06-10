CXX = g++
CXXFLAGS = -g3 -O0 -Wall --std=c++11

all: setops_test majors

setops_test: setops_test.cpp setops.o 
	g++ -g -Wall setops_test.cpp setops.o -o setops_test $(CXXFLAGS)


majors: majors.cpp setops.o
	g++ -g -Wall majors.cpp setops.o -o majors $(CXXFLAGS)

setops.o: setops.cpp setops.h
	g++ -g -Wall -c setops.cpp -o setops.o $(CXXFLAGS)


clean: 

.PHONY: clean