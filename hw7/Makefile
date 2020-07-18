all: bst-test sat_solver

sat_solver: sat_solver.cpp
	g++ -g -std=c++11 $^ -o $@

bst-test: bst-test.cpp
	g++ -g -Wall -std=c++11 $^ -o $@