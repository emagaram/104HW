CXX = g++
CXXFLAGS = -g3 -O0 -Wall --std=c++11

setops.o: setops.cpp setops.h
	g++ -g -Wall -c setops.cpp -o setops.o


setops_test: setops.o setops_test.cpp
	g++ -g -Wall setops.o setops_test.cpp -o setops_test

clean: 

.PHONY: clean