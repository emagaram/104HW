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
#include <iostream>
#include <ctime>
#include <chrono>

#define private public
#define protected public

#include "../../util.h"
#include "../../datetime.h"
#include "../../twiteng.h"
#undef private
#undef protected

// Add a tweet with no text
TEST(AddTweet, NoText)
{
	TwitEng te;
	DateTime dt;
	ASSERT_FALSE(te.parse((char*)"data_files/short.dat")) << "Expected for parse to return false";

	te.addTweet("Tommy", dt, "");

	te.dumpFeeds();

	std::ifstream mark("Mark.feed"); 
	std::ifstream tommy("Tommy.feed"); 

	int markNumLines = 0; 
	int tommyNumLines = 0; 

	std::string line; 

	while (std::getline(mark, line)) markNumLines++; 

	while (std::getline(tommy, line)) tommyNumLines++; 

	EXPECT_EQ(markNumLines, tommyNumLines) << "Feed files should be identical";

	EXPECT_EQ(markNumLines, 3) << "Expected .feed files to be 3 lines long, but the number of lines was actually " << markNumLines; 

}

// Add a tweet with a relatively short amount of text
TEST(AddTweet, AddShort)
{
	TwitEng te;
	DateTime dt;
	ASSERT_FALSE(te.parse((char*)"data_files/short.dat")) << "Expected for parse to return false";

	te.addTweet("Tommy", dt, "This is a short tweet");

	te.dumpFeeds();

	std::ifstream mark("Mark.feed"); 
	std::ifstream tommy("Tommy.feed"); 

	int markNumLines = 0; 
	int tommyNumLines = 0; 

	std::string line; 

	while (std::getline(mark, line)) markNumLines++; 

	while (std::getline(tommy, line)) tommyNumLines++; 

	EXPECT_EQ(markNumLines, tommyNumLines) << "Feed files should be identical";

	EXPECT_EQ(markNumLines, 3) << "Expected .feed files to be 3 lines long, but the number of lines was actually " << markNumLines; 
}

// Add a tweet with a moderate amount of text
TEST(AddTweet, AddMedium)
{
	TwitEng te;
	DateTime dt;
	ASSERT_FALSE(te.parse((char*)"data_files/short.dat")) << "Expected for parse to return false";

	te.addTweet("Tommy", dt, "This is tweet is substantially longer than the previous tweet that was added to an engine");

	te.dumpFeeds();

	std::ifstream mark("Mark.feed"); 
	std::ifstream tommy("Tommy.feed"); 

	int markNumLines = 0; 
	int tommyNumLines = 0; 

	std::string line; 

	while (std::getline(mark, line)) markNumLines++; 

	while (std::getline(tommy, line)) tommyNumLines++; 

	EXPECT_EQ(markNumLines, tommyNumLines) << "Feed files should be identical";

	EXPECT_EQ(markNumLines, 3) << "Expected .feed files to be 3 lines long, but the number of lines was actually " << markNumLines; 
}

// Add a tweet with a relatively large amount of text 
TEST(AddTweet, AddLong)
{
	TwitEng te;
	DateTime dt;
	ASSERT_FALSE(te.parse((char*)"data_files/short.dat")) << "Expected for parse to return false";

	te.addTweet("Tommy", dt, "Call me Ishmael. Some years ago - never mind how long precisely - having little or no money in my purse, and nothing particular to interest me on shore, I thought I would sail about a little and see the watery part of the world. It is a way I have of driving off the spleen and regulating the circulation. Whenever I find myself growing grim about the mouth; whenever it is a damp, drizzly November in my soul; whenever I find myself involuntarily pausing before coffin warehouses, and bringing up the rear of every funeral I meet; and especially whenever my hypos get such an upper hand of me, that it requires a strong moral principle to prevent me from deliberately stepping into the street, and methodically knocking people's hats off - then, I account it high time to get to sea as soon as I can");

	te.dumpFeeds();

	std::ifstream mark("Mark.feed"); 
	std::ifstream tommy("Tommy.feed"); 

	int markNumLines = 0; 
	int tommyNumLines = 0; 

	std::string line; 

	while (std::getline(mark, line)) markNumLines++; 

	while (std::getline(tommy, line)) tommyNumLines++; 

	EXPECT_EQ(markNumLines, tommyNumLines) << "Feed files should be identical";

	EXPECT_EQ(markNumLines, 3) << "Expected .feed files to be 3 lines long, but the number of lines was actually " << markNumLines; 
}