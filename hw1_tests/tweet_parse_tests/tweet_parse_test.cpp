//
// CS104 HW1 tweet parse
//

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
std::string checkTweets(std::string const & testName, std::string const & inputContents, bool useValgrind = true)
{
	// Prepares to write input/output files
	std::string executablePath = TWEET_PARSE_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/tweet_parse_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";
	std::string stdoutFilePath = testFolder + "/stdout.txt";
	
	// write tweets to file
	std::ofstream inputWriter(inputFilePath);
	inputWriter << inputContents << std::endl;

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath, outputFilePath}, stdoutFilePath, useValgrind);
	testing::AssertionResult result = runner.execute();
	return stdoutFilePath;
	// read output
	/*{
		std::ifstream outputFile(stdoutFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}
		std::string numTweetsRead;
		std::getline (outputFile, numTweetsRead); //Get Line of num Tweets
		std::regex tweetRegex = std::regex(".*Number of Tweets\\s*=\\s*" + std::to_string(numTweets), std::regex_constants::icase);
		if (!std::regex_match(numTweetsRead, tweetRegex))
		{
			return testing::AssertionFailure();
		}
	}*/
};

testing::AssertionResult checkNumTweets(std::string stdoutFilePath, int correctNumTweets)
{
	std::ifstream outputFile(stdoutFilePath);
	if(!outputFile)
	{
		return testing::AssertionFailure() << "Couldn't open output file " << stdoutFilePath;
	}
	std::string numTweetsRead;
	std::getline (outputFile, numTweetsRead); //Get Line of num Tweets
	std::regex tweetRegex = std::regex(".*Number of Tweets\\s*=\\s*" + std::to_string(correctNumTweets), std::regex_constants::icase);
	if (!std::regex_match(numTweetsRead, tweetRegex))
	{
		return testing::AssertionFailure() << "Incorrect number of tweets reported/Could not find line";
	}
	return testing::AssertionSuccess();
}

testing::AssertionResult checkUsers(std::string stdoutFilePath, std::vector<std::string>& correctUsers)
{
	std::ifstream outputFile(stdoutFilePath);
	if(!outputFile)
	{
		return testing::AssertionFailure() << "Couldn't open output file " << stdoutFilePath;
	}
	std::vector<std::string> users;
	std::regex endUsersRegex = std::regex(".*Hashtags.*", std::regex_constants::icase);
	std::string line;
	std::getline(outputFile, line); // Num Tweets
	std::getline(outputFile, line); // Unique Users
	std::getline(outputFile, line); // First user
	while (!outputFile.fail() && !std::regex_match(line, endUsersRegex))
	{
		users.push_back(line);
		getline(outputFile, line);
	}
	if (users.size() != correctUsers.size())
	{
		return testing::AssertionFailure() << "Incorrect number of users found";
	}
	for (unsigned int i = 0; i < users.size(); i++)
	{
		if (users[i] != correctUsers[i])
		{
			return testing::AssertionFailure() << "Incorrect user/order of users";
		}
	}
	return testing::AssertionSuccess();
}

testing::AssertionResult checkHashtags(std::string stdoutFilePath, std::vector<std::string>& correctHashtags)
{
	std::ifstream outputFile(stdoutFilePath);
	if(!outputFile)
	{
		return testing::AssertionFailure() << "Couldn't open output file " << stdoutFilePath;
	}
	std::vector<std::string> hashtags;
	std::regex endUsersRegex = std::regex(".*Hashtags.*", std::regex_constants::icase);
	std::string line;
	while (!outputFile.fail() && !std::regex_match(line, endUsersRegex))
	{
		getline(outputFile, line);
	}
	while (!outputFile.fail())
	{
		getline(outputFile, line);
		if (!std::regex_match(line, std::regex("^\\s*$")))
		{
			hashtags.push_back(line);
		}
	}
	if (hashtags.size() != correctHashtags.size())
	{
		return testing::AssertionFailure() << "Incorrect number of hashtags";
	}
	for (unsigned int i = 0; i < hashtags.size(); i++)
	{
		if (hashtags[i] != correctHashtags[i])
		{
			return testing::AssertionFailure() << "Incorrect hashtag/order of hashtags";
		}
	}
	return testing::AssertionSuccess();
}

const std::string easytweet =
"@a #b easy tweet\n";

const std::string tweet1 =
"Hey @student2 isn't #cs104 the best? a\n"                                                                                                                                                                       
"@prof when is HW1 due? #sleepinginclass a\n"
"@student1 @student2 you should talk to @prof a\n";

const std::string tweet2 = 
"@a asdf #xx @b asfdf #yy @c asdf #zz a\n";

const std::string tweet3 = 
"#aa @x @x #aa a\n"
"#bb @y @x #cc @abc a\n";

TEST(TestTweetParse, EasyTweetNum)
{
	std::string filepath = checkTweets("NormalInput1", easytweet, true);
	ASSERT_TRUE(checkNumTweets(filepath, 1));
}

TEST(TestTweetParse, NumTweets1)
{
	std::string filepath = checkTweets("NormalInput1", tweet1, true);
  ASSERT_TRUE(checkNumTweets(filepath, 3));
}

TEST(TestTweetParse, NumTweets2)
{
	std::string filepath = checkTweets("NumTweets2", tweet2, true);
  ASSERT_TRUE(checkNumTweets(filepath, 1));

}

TEST(TestTweetParse, NumTweets3)
{
	std::string filepath = checkTweets("NumTweets3", tweet3, true);
	ASSERT_TRUE(checkNumTweets(filepath,2));
}

TEST(TestTweetParse, EasyTweetUsers)
{
	std::vector<std::string> correctUsers = {"a"};
	std::string filepath = checkTweets("EasyTweetUsers", easytweet, true);
	ASSERT_TRUE(checkUsers(filepath, correctUsers));
}

TEST(TestTweetParse, TestUsers1)
{
	std::vector<std::string> correctUsers = {"student2", "prof", "student1"};
	std::string filepath = checkTweets("TestUsers1", tweet1, true);
	ASSERT_TRUE(checkUsers(filepath, correctUsers));
}

TEST(TestTweetParse, TestUsers2)
{
	std::vector<std::string> correctUsers = {"a", "b", "c"};
	std::string filepath = checkTweets("TestUsers2", tweet2, true);
	ASSERT_TRUE(checkUsers(filepath, correctUsers));
}

TEST(TestTweetParse, TestUsers3)
{
	std::vector<std::string> correctUsers = {"x", "y", "abc"};
	std::string filepath = checkTweets("TestUsers3", tweet3, true);
	ASSERT_TRUE(checkUsers(filepath, correctUsers));
}

TEST(TestTweetParse, EasyTweetHashtags)
{
	std::vector<std::string> correctHashtags = {"b"};
	std::string filepath = checkTweets("TestHashtags1", easytweet, true);
	ASSERT_TRUE(checkHashtags(filepath, correctHashtags));
}

TEST(TestTweetParse, TestHashtags1)
{
	std::vector<std::string> correctHashtags = {"cs104", "sleepinginclass"};
	std::string filepath = checkTweets("TestHashtags1", tweet1, true);
	ASSERT_TRUE(checkHashtags(filepath, correctHashtags));
}

TEST(TestTweetParse, TestHashtags2)
{
	std::vector<std::string> correctHashtags = {"xx", "yy", "zz"};
	std::string filepath = checkTweets("TestHashtags1", tweet2, true);
	ASSERT_TRUE(checkHashtags(filepath, correctHashtags));
}
TEST(TestTweetParse, TestHashtags3)
{
	std::vector<std::string> correctHashtags = {"aa", "bb", "cc"};
	std::string filepath = checkTweets("TestHashtags3", tweet3, true);
	ASSERT_TRUE(checkHashtags(filepath, correctHashtags));
}


TEST(TestTweetParse, BadInput)
{
	std::string executablePath = TWEET_PARSE_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/tweet_parse/testFiles/BadInput";
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";
	std::string stdoutFilePath = testFolder + "/stdout.txt";

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath, outputFilePath}, stdoutFilePath, true);
	testing::AssertionResult result = runner.execute();
	std::ifstream outfile(stdoutFilePath);
	std::string line;
	getline(outfile, line); // Make sure they output something
}
