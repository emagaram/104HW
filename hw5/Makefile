# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
CFLAGS=
BLANK= I$(IDIR) -std=c++11 -ggdb
BIN_DIR  = bin
DELETE_FILE = rm -f
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: twitter Tests

Tests: Tests.cpp datetime.o util.o
	g++ -g -Wall -std=c++11 Tests.cpp datetime.o util.o -o Tests

twitter: twitter.cpp twiteng.o user.o handler.o cmdhandler.o datetime.o tweet.o util.o
	g++ -g -Wall -std=c++11 twitter.cpp twiteng.o user.o handler.o cmdhandler.o datetime.o tweet.o util.o -o twitter 

handler.o: handler.h handler.cpp
	g++ -g -Wall -c -std=c++11 handler.cpp -o handler.o 

cmdhandler.o: cmdhandler.h cmdhandler.cpp
	g++ -g -Wall -c -std=c++11 cmdhandler.cpp -o cmdhandler.o 


twiteng.o: twiteng.h twiteng.cpp
	g++ -g -Wall -c -std=c++11 twiteng.cpp -o twiteng.o 

tweet.o: tweet.cpp tweet.h
	g++ -g -Wall -c -std=c++11 tweet.cpp -o tweet.o 
	
user.o: user.h user.cpp
	g++ -g -Wall -c -std=c++11 user.cpp -o user.o 

datetime.o: datetime.cpp datetime.h
	g++ -g -Wall -c -std=c++11 datetime.cpp -o datetime.o 

util.o: util.cpp util.h
	g++ -g -Wall -c -std=c++11 util.cpp -o util.o



.PHONY:  clean


clean:
	$(DELETE_FILE) *.o	
	$(DELETE_FILE) *.exe