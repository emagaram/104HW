#include <gtest/gtest.h>

//#include <user_code_runner.h>
//#include <random_generator.h>
//#include <misc_utils.h>

//#include <kwsys/SystemTools.hxx>
//#include <kwsys/RegularExpression.hxx>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <twiteng.h>
#include <tweet.h>
#include <user.h>
#include <array>
#include <algorithm>
#include <util.h>
#include <user.h>
#define RANDOM_SEED 42

using namespace std;

char input_file[] = "twit_input1.dat";
char double_hashtag_file[] = "double_tag.dat";
//Check if two vectors contain the same contents
void checkContents(vector<string> correct, vector<Tweet*> &results)
{
	sort(correct.begin(), correct.end(), greater<string>());
	sort(results.begin(), results.end(), TweetComp());
		
	ASSERT_TRUE(correct.size() == results.size());
	
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stringstream s;
		s << *results[i];
		regex re(correct[i] + "\\s*");
		EXPECT_TRUE(regex_match(s.str(), re));
	}
}


TEST(AndTest, NoHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {};
	vector<Tweet*> results = twit.search(search, 0);
	EXPECT_EQ(0, results.size());
	// Not super well defined behavior, just don't segfault
}

TEST(AndTest, MissingHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception & e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {"notpresent"};
	vector<Tweet*> results = twit.search(search, 0);
}

TEST(AndTest, TwoHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception & e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {"b", "c"};
	vector<Tweet*> results = twit.search(search, 0);
	vector<string> correct = {"2019-05-20 12:34:56 Eric #a #b #c #d #e #f #g #h #i #j #k",
														"2019-05-20 12:34:57 Eric #b #c #d #e #f #g #h #i #j #k"};
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}

TEST(AndTest, OneHashTags)
{	
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files";
	}
	vector<string> search {"c"};
	vector<Tweet*> results = twit.search(search, 0);
	vector<string> correct = {"2019-05-20 12:34:57 Eric #b #c #d #e #f #g #h #i #j #k",
	"2019-05-20 12:34:56 Eric #a #b #c #d #e #f #g #h #i #j #k",
	"2019-05-20 12:34:58 Eric #c #d #e #f #g #h #i #j #k"};
										
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}

TEST(OrTest, NoHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {};
	vector<Tweet*> results = twit.search(search, 1);
	EXPECT_EQ(0, results.size());
	// Not super well defined behavior, just don't segfault
}

TEST(OrTest, MissingHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception & e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {"notpresent"};
	vector<Tweet*> results = twit.search(search, 1);
}

TEST(OrTest, TwoHashTags)
{
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception & e)
	{
		FAIL() << "Could Not Parse Files, come in for regrade, all tests will fail";
	}
	vector<string> search {"b", "c"};
	vector<Tweet*> results = twit.search(search, 1);
	vector<string> correct = {"2019-05-20 12:34:58 Eric #c #d #e #f #g #h #i #j #k",
											 	"2019-05-20 12:34:57 Eric #b #c #d #e #f #g #h #i #j #k",
												"2019-05-20 12:34:56 Eric #a #b #c #d #e #f #g #h #i #j #k"};
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}

TEST(OrTest, OneHashTags)
{	
	TwitEng twit;
	try
	{
		twit.parse(input_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files";
	}
	vector<string> search {"c"};
	vector<Tweet*> results = twit.search(search, 1);
	vector<string> correct = {"2019-05-20 12:34:58 Eric #c #d #e #f #g #h #i #j #k",
											 	"2019-05-20 12:34:57 Eric #b #c #d #e #f #g #h #i #j #k",
												"2019-05-20 12:34:56 Eric #a #b #c #d #e #f #g #h #i #j #k"};
										
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}

TEST(OrTest, DoubleTags)
{	
	TwitEng twit;
	try
	{
		twit.parse(double_hashtag_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files";
	}
	vector<string> search {"tag"};
	vector<Tweet*> results = twit.search(search, 1);
	vector<string> correct = {"2019-05-20 12:34:56 Eric #tag #tag"};
										
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}

TEST(AndTest, DoubleTags)
{	
	TwitEng twit;
	try
	{
		twit.parse(double_hashtag_file);
	}
	catch(const exception& e)
	{
		FAIL() << "Could Not Parse Files";
	}
	vector<string> search {"tag"};
	vector<Tweet*> results = twit.search(search, 1);
	vector<string> correct = {"2019-05-20 12:34:56 Eric #tag #tag"};
										
	stringstream stream;
	for(unsigned int i = 0; i < results.size(); i++)
	{
		stream << *results[i] << endl;
	}
	string s = stream.str();
	checkContents(correct, results);
}
