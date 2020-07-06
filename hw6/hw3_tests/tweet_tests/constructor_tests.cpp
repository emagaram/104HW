#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#define private public
#define protected public


#include "../../util.h"
#include "../../tweet.h"
#include "../../user.h"
#include "../../datetime.h"

#undef private
#undef protected

// Test default constructor
TEST(TweetConstructor, Default) 
{
	Tweet* t = new Tweet(); 

	int year = t->time().year; 

	delete t;
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	int exp_year = 1900 + timeinfo->tm_year;
  
	EXPECT_EQ(exp_year, year) << "Expected for the year to be 2019, but the year is actually " << year; 
}

// Test constructor with no text
TEST(TweetConstructor, NoText)
{
	User* a = new User("Charlie_Chaplin"); 
	Tweet* t = new Tweet(a, DateTime(), std::string(""));	

	std::string text = t->text(); 

	
	delete a;
	delete t; 

	EXPECT_EQ("", text) << "Expected for the Tweet's text to be blank, but it was actually " << text; 
}

// Test constructor with text
TEST(TweetConstructor, WithText) 
{
	User* a = new User("Carl_Wheezer"); 
	Tweet* t = new Tweet(a, DateTime(), std::string("Are you going to finish that #croissant?")); 

	std::string text = t->text(); 

	delete a; 
	delete t; 

	EXPECT_EQ("Are you going to finish that #croissant?", text) << "Expected for the Tweet's text to be \"Are you going to finish that croissant?\", but it was actually " << text; 
}
