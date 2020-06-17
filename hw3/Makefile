# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
CFLAGS=-I$(IDIR) -std=c++11 -ggdb
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: twitter

twitter: twitter.cpp twiteng.o user.o handler.o cmdhandler.o datetime.o tweet.o util.o
	g++ -g -Wall twitter.cpp twiteng.o user.o handler.o cmdhandler.o datetime.o tweet.o util.o -o twitter

handler.o: handler.h handler.cpp
	g++ -g -Wall -c handler.cpp -o handler.o $(CFLAGS)

cmdhandler.o: cmdhandler.h cmdhandler.cpp
	g++ -g -Wall -c cmdhandler.cpp -o cmdhandler.o $(CFLAGS)


twiteng.o: twiteng.h twiteng.cpp
	g++ -g -Wall -c twiteng.cpp -o twiteng.o $(CFLAGS)

tweet.o: tweet.cpp tweet.h
	g++ -g -Wall -c tweet.cpp -o tweet.o $(CFLAGS)
	
user.o: user.h user.cpp
	g++ -g -Wall -c user.cpp -o user.o $(CFLAGS)

datetime.o: datetime.cpp datetime.h
	g++ -g -Wall -c datetime.cpp -o datetime.o $(CFLAGS)

util.o: util.cpp util.h
	g++ -g -Wall -c util.cpp -o util.o $(CFLAGS)



.PHONY:  clean


clean: