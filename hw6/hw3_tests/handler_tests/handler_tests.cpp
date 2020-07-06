#include <gtest/gtest.h>
#define protected public
#include <twiteng.h> 
#include <util.h>
#include <tweet.h>
#include <user.h>
#include <cmdhandler.h>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

char input_file[] = "twit_input.dat";
//0 is and, 1 is or
//Tests whether output from process is same as search results
void processCommand(vector<string> terms, int strat, Handler* h, TwitEng twit = TwitEng())
{
	string command;
	if (strat == 0)
	{
		command = "AND";
	}
	else if(strat == 1)
	{
		command = "OR";
	}
	twit.parse(input_file);
	stringstream s;
	copy(terms.begin(), terms.end(), ostream_iterator<string>(s, " "));
	streambuf* cout_sbuf = cout.rdbuf();
	ofstream handler_out("handler_out.txt");
	cout.rdbuf(handler_out.rdbuf());
	h->handle(&twit, command, s);
	handler_out.close();
	ifstream handler_in("handler_out.txt");

	ofstream process_out("process_out.txt");
	cout.rdbuf(process_out.rdbuf());
	vector<Tweet*> results;
	results = twit.search(terms, strat);
	displayHits(results);
	string line1;
	string line2;
	process_out.close();
	ifstream process_in("process_out.txt");
	cout.rdbuf(cout_sbuf);
	while (getline(process_in, line1) && getline(handler_in, line2))
	{
		ASSERT_EQ(line1, line2);

	}
}

TEST(AndHandlerTest, CanHandle)
{
	Handler* h = new AndHandler(nullptr);
	h->canHandle("AND");
	delete h;
}

TEST(AndHandlerTest, ProcessAndOneHashtag)
{
	Handler* h = new AndHandler();
	vector<string> search = {"c"};
	processCommand(search, 0, h);
	delete h;
}
TEST(AndHandlerTest, ProcessAndTwoHashtags)
{
	Handler* h = new AndHandler();
	vector<string> search = {"c", "d"};
	processCommand(search, 0, h);
	delete h;
}

TEST(AndHandlerTest, ProcessAndManyHashtag)
{
	Handler* h = new AndHandler();
	vector<string> search = {"c", "e", "f", "g"};
	processCommand(search, 0, h);
	delete h;
}

TEST(AndHandlerTest, ProcessAndNoResults)
{
	Handler* h = new AndHandler();
	vector<string> search = {"z"};
	processCommand(search, 0, h);
	delete h;
}


TEST(OrHandlerTest, CanHandle)
{
	Handler* h = new OrHandler(nullptr);
	h->canHandle("OR");
	delete h;
}

TEST(OrHandlerTest, ProcessOrOneHashtag)
{
	Handler* h = new OrHandler();
	vector<string> search = {"c"};
	processCommand(search, 1, h);
	delete h;
}
TEST(OrHandlerTest, ProcessOrTwoHashtags)
{
	Handler* h = new OrHandler();
	vector<string> search = {"c", "d"};
	processCommand(search, 1, h);
	delete h;
}

TEST(OrHandlerTest, ProcessOrManyHashtag)
{
	Handler* h = new OrHandler();
	vector<string> search = {"c", "e", "f", "g"};
	processCommand(search, 1, h);
	delete h;
}

TEST(OrHandlerTest, ProcessOrNoResults)
{
	Handler* h = new OrHandler();
	vector<string> search = {"z"};
	processCommand(search, 1, h);
	delete h;
}

TEST(TweetHandlerTest, CanHandle)
{
	Handler* h = new TweetHandler();
	ASSERT_TRUE(h->canHandle("TWEET"));
	delete h;
}

TEST(TweetHandlerTest, AddTweetThenSearch)
{
	Handler* h = new TweetHandler();
	stringstream s("Eric Tweet it's a new tweet #sweet");
	TwitEng twit;
	twit.parse(input_file);
	string command = "TWEET";
	h->handle(&twit, command, s);	
	vector<string> terms = {"sweet"};
	vector<Tweet*> results = twit.search(terms, 1);
	ASSERT_EQ(results.size(), 1);
	regex re(".*it's a new tweet #sweet");
	stringstream ss;
	ss << *results[0];
	ASSERT_TRUE(regex_match( ss.str(), re));
	delete h;
}

TEST(TweetHandlerTest, AddTweetInvalidUser)
{
	Handler* h = new TweetHandler();
	stringstream s("Sean Tweet it's a new tweet #sweet");
	TwitEng twit;
	twit.parse(input_file);
	string command = "TWEET";
	h->handle(&twit, command, s);	
	//Don't Crash
	delete h;
}

TEST(TweetHandlerTest, CaseInsensitiveHashtagTest)
{
	Handler* h = new TweetHandler();
	stringstream s("Eric Tweet it's a new tweet #Sweet");
	TwitEng twit;
	twit.parse(input_file);
	string command = "TWEET";
	h->handle(&twit, command, s);	
	vector<string> terms = {"sweet"};
	vector<Tweet*> results = twit.search(terms, 1);
	ASSERT_EQ(results.size(), 1);
	regex re(".*it's a new tweet #Sweet*");
	stringstream ss;
	ss << *results[0];
	ASSERT_TRUE(regex_match( ss.str(), re));
	delete h;
}
