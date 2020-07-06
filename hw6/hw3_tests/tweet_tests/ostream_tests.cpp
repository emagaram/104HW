#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>
#include <regex>
#include <sstream>
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
#include "../../datetime.h"
#include "../../user.h"

#undef private
#undef protected

// Output a Tweet that contains no text 
TEST(OStream, EmptyTweet)
{
	std::stringstream ss;
	User* a = new User("Alvin");
	DateTime d(12, 0, 0, 1999, 1, 10);
	Tweet t(a, d, ""); 
	ss << t; 
	std::string s = ss.str(); 

	EXPECT_EQ("1999-01-10 12:00:00 Alvin", s.substr(0,25)) << "Expected output to contain \'1999-1-10 12:00:00 Alvin\'"; 

	delete a;
}

// Output a Tweet that is relatively short
TEST(OStream, ShortTweet)
{
	std::stringstream ss;
	User* a = new User("Simon");
	DateTime d(12, 0, 0, 1999, 1, 10);
	Tweet t(a, d, "I am a high-pitched singing chipmunk!"); 
	ss << t; 
	std::string s = ss.str(); 

	EXPECT_EQ("1999-01-10 12:00:00 Simon I am a high-pitched singing chipmunk!", s.substr(0,64)) << "Expected output to contain \'1999-1-10 12:00:00 Simon I am a high-pitched singing chipmunk!\'"; 

	delete a;
}

// Output a Tweet that is relatively long
TEST(OStream, LongTweet)
{
	std::stringstream ss;
	User* a = new User("Theodore");
	DateTime d(12, 0, 0, 1999, 1, 10);
	Tweet t(a, d, "I am also a high-pitched singing chipmunk! My tweets tend to be a little bit more verbose than those of my two brothers, Simon and Alvin"); 
	ss << t; 
	std::string s = ss.str(); 

	EXPECT_EQ("1999-01-10 12:00:00 Theodore I am also a high-pitched singing chipmunk! My tweets tend to be a little bit more verbose than those of my two brothers, Simon and Alvin", s.substr(0,166)) << "Expected output to contain \'1999-1-10 12:00:00 Theodore I am also a high-pitched singing chipmunk! My tweets tend to be a little bit more verbose than those of my two brothers, Simon and Alvin\'"; 

	delete a;
}