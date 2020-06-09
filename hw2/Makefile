CXX = g++
CXXFLAGS = -g3 -O0 -Wall --std=c++11

all: setops_test

setops_test: setops_test.cpp setops.o 
	g++ -g -Wall setops_test.cpp setops.o -o setops_test


setops.o: setops.cpp setops.h
	g++ -g -Wall -c setops.cpp -o setops.o



clean: 

.PHONY: clean