# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
CFLAGS=-I$(IDIR) -std=c++11 -ggdb
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: user

user: user.cpp
	g++ -g -Wall user.cpp -o user $(CFLAGS)
	
util: util.h util.cpp
	g++ -g -Wall util.cpp util.h -o util $(CFLAGS)



.PHONY:  clean


clean:
	-@echo "--- All Clean!---"