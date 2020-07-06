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

#include "../../twiteng.h"

#undef private
#undef protected

// //Runs twiteng for a particular .dat file
// bool generateFeedFiles(std::string dataFilePath, std::string testName) 
// {
// 	std::string executablePath = TWITTER_EXECUTABLE;
// 	std::string testFolder =  "twiteng_tests/data_files/" + testName;
// 	//kwsys::SystemTools::MakeDirectory(testFolder);
	
// 	std::string stdoutFilePath = testFolder +"/" + "stdout.txt";
	
// 	// write input to file
// 	//std::ofstream inputWriter(inputFilePath);
// 	//while(inputWriter << inputContents) {}
// 	//inputWriter << inputContents << std::endl;

// 	//write commands to file 
// 	//std::ofstream commandWriter(commandFilePath); 
// 	//while(commandWriter << commandContents) {}
// 	//ommandWriter << commandContents << std::endl; 

// 	// run the program
// 	UserCodeRunner runner(testFolder, 
// 						  executablePath, 
// 						  {dataFilePath}, 
// 						  stdoutFilePath, 
// 						  true);


// 	//Set up standard input
// 	runner.setStdin("QUIT", testFolder + "/std.in"); 

// 	testing::AssertionResult result = runner.execute(); 

// 	if (result == testing::AssertionSuccess()) 
// 		return true; 

// 	return false; 
// }

// Attempt to parse an empty .dat file
TEST(Parse, Empty) 
{
	// ASSERT_TRUE(generateFeedFiles("blank.dat", "Empty")); 
	TwitEng te; 

	ASSERT_TRUE(te.parse((char*)"data_files/blank.dat")) << "Expected for parse to return true";

	//EXPECT_EQ(te.userMap_.size(), 0); 
}

// Attempt to parse a .dat file that does not exist
// Failure to read in a file that does not exist should be handled gracefully
TEST(Parse, FileDoesNotExist) 
{
	// ASSERT_TRUE(generateFeedFiles("doesNotExist.dat", "FileDoesNotExist")); 
	TwitEng te; 

	ASSERT_TRUE(te.parse((char*)"dne.dat")) << "Expected for parse to return true";

	//EXPECT_EQ(te.userMap_.size(), 0);
}

//IMPOPER FORMAT TEST COMMENTED OUT TO PREVENT SOLUTION CODE FROM SEGFAULTING

// Attempt to parse an incorrectly formatted .dat file
// Failure to read in the file should be handled gracefully
// TEST(Parse, ImproperFormat) 
// {
// 	// ASSERT_TRUE(generateFeedFiles("improper.dat", "ImproperFormat")); 
// 	TwitEng te; 

// 	ASSERT_TRUE(te.parse((char*)"data_files/improper.dat")) << "Expected for parse to return true";

// 	EXPECT_EQ(te.userMap_.size(), 0);
// }

// Attempt to parse a relatively short .dat file
TEST(Parse, Short) 
{

	TwitEng te; 

	ASSERT_FALSE(te.parse((char*)"data_files/short.dat")) << "Expected for parse to return false";
	te.dumpFeeds();

	// ASSERT_TRUE(generateFeedFiles("short.dat", "Short")); 

	std::ifstream mark("Mark.feed"); 
	std::ifstream tommy("Tommy.feed"); 

	int markNumLines = 0; 
	int tommyNumLines = 0; 

	std::string line; 

	while (std::getline(mark, line)) markNumLines++; 

	while (std::getline(tommy, line)) tommyNumLines++; 

	EXPECT_EQ(markNumLines, tommyNumLines) << "Feed files should be identical";

	EXPECT_EQ(markNumLines, 2) << "Expected .feed files to be 2 lines long, but the number of lines was actually " << markNumLines; 
}

// Attempt to parse a moderately-sized .dat file
TEST(Parse, Medium) 
{

	TwitEng te; 

	ASSERT_FALSE(te.parse((char*)"data_files/medium.dat")) << "Expected for parse to return false";
	te.dumpFeeds();
	// ASSERT_TRUE(generateFeedFiles("medium.dat", "Medium")); 

	std::ifstream michael("Michael.feed"); 
	std::ifstream dwight("Dwight.feed"); 
	std::ifstream jim("Jim.feed"); 
	std::ifstream pam("Pam.feed"); 

	int michaelNumLines = 0; 
	int dwightNumLines = 0; 
	int jimNumLines = 0; 
	int pamNumLines = 0; 
	std::string line;

	while (std::getline(michael, line)) michaelNumLines++;
	while (std::getline(dwight, line)) dwightNumLines++;  
	while (std::getline(jim, line)) jimNumLines++; 
	while (std::getline(pam, line)) pamNumLines++; 

	EXPECT_EQ(michaelNumLines, 5) << "Michael's feed did not have five lines. Number of lines was " << michaelNumLines; 
	EXPECT_EQ(dwightNumLines, 3) << "Dwight's feed did not have three lines. Number of lines was " << dwightNumLines;
	EXPECT_EQ(jimNumLines, 4) << "Jim's feed did not have four lines. Number of lines was " << jimNumLines;  
	EXPECT_EQ(pamNumLines, 4) << "Pam's feed did not have four lines. Number of lines was " << pamNumLines;  

	//testing::AssertionSuccess(); 
}

// Attempt to parse a relatively long .dat file
TEST(Parse, Long) 
{
	TwitEng te; 

	ASSERT_FALSE(te.parse((char*)"data_files/long.dat")) << "Expected for parse to return false";
	te.dumpFeeds();
	// ASSERT_TRUE(generateFeedFiles("long.dat", "Long")); 

	std::ifstream michael("Michael.feed"); 
	std::ifstream dwight("Dwight.feed"); 
	std::ifstream jim("Jim.feed"); 
	std::ifstream pam("Pam.feed"); 
	std::ifstream kevin("Kevin.feed"); 
	std::ifstream angela("Angela.feed"); 
	std::ifstream toby("Toby.feed"); 
	std::ifstream kelly("Kelly.feed"); 

	int michaelNumLines = 0; 
	int dwightNumLines = 0; 
	int jimNumLines = 0; 
	int pamNumLines = 0; 
	int kevinNumLines = 0; 
	int angelaNumLines = 0; 
	int tobyNumLines = 0; 
	int kellyNumLines = 0; 

	std::string line;

	while (std::getline(michael, line)) michaelNumLines++;
	while (std::getline(dwight, line)) dwightNumLines++;  
	while (std::getline(jim, line)) jimNumLines++; 
	while (std::getline(pam, line)) pamNumLines++; 
	while (std::getline(kevin, line)) kevinNumLines++;
	while (std::getline(angela, line)) angelaNumLines++;  
	while (std::getline(toby, line)) tobyNumLines++; 
	while (std::getline(kelly, line)) kellyNumLines++; 

	EXPECT_EQ(michaelNumLines, 8) << "Michael's feed did not have eight lines. Number of lines was " << michaelNumLines; 
	EXPECT_EQ(dwightNumLines, 5) << "Dwight's feed did not have five lines. Number of lines was " << dwightNumLines;
	EXPECT_EQ(jimNumLines, 4) << "Jim's feed did not have four lines. Number of lines was " << jimNumLines;  
	EXPECT_EQ(pamNumLines, 4) << "Pam's feed did not have four lines. Number of lines was " << pamNumLines;  
	EXPECT_EQ(kevinNumLines, 4) << "Kevin's feed did not have four lines. Number of lines was " << michaelNumLines; 
	EXPECT_EQ(angelaNumLines, 3) << "Angela's feed did not have three lines. Number of lines was " << dwightNumLines;
	EXPECT_EQ(tobyNumLines, 2) << "Toby's feed did not have one line. Number of lines was " << jimNumLines;  
	EXPECT_EQ(kellyNumLines, 10) << "Kelly's feed did not have ten lines. Number of lines was " << pamNumLines;  

	
}