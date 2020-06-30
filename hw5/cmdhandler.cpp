#include "cmdhandler.h"
#include "util.h"
#include <sstream>
#include <ctime>
//#pragma warning(disable : 4996)
using namespace std;

SaveHandler::SaveHandler()
{
}
SaveHandler::SaveHandler(Handler *next)
	: Handler(next)
{
}

bool SaveHandler::canHandle(const std::string &cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng *eng, std::istream &instr) const
{

	std::string fileName;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet *> output;
	std::getline(instr, line);
	std::stringstream ss(line); //SAVE twitter_save.txt
	ss >> fileName;
	std::ofstream ofile(fileName);
	std::map<std::string, User *> copyUsers = eng->getUsers();
	ofile << copyUsers.size() << std::endl;
	std::map<std::string, User *>::iterator userIt = copyUsers.begin();

	std::list<Tweet *> allTweets;

	while (userIt != copyUsers.end())
	{
		User *u = userIt->second;
		
		ofile << u->name() << " ";

		std::set<User *> copyFollowing = u->following();
		std::set<User *>::iterator followIt = copyFollowing.begin();
		while (followIt != copyFollowing.end())
		{
			ofile << (*followIt)->name() << " ";
			followIt++;
		}
		ofile << std::endl;
		if (allTweets.size() == 0)
		{
			allTweets = u->tweets();
		}
		else
		{
			std::list<Tweet*> uTweetsCopy = u->tweets();
			allTweets.insert(allTweets.end(), uTweetsCopy.begin(),uTweetsCopy.end());
		}
		userIt++;
	}
	std::vector<Tweet *> copyTweets(allTweets.begin(), allTweets.end());
	std::sort(copyTweets.begin(), copyTweets.end(), TweetComp());
	std::vector<Tweet *>::iterator tweetIt = copyTweets.begin();
	while (tweetIt != copyTweets.end())
	{
		ofile << **tweetIt << std::endl;
		tweetIt++;
	}

	return HANDLER_OK;
}

FollowHandler::FollowHandler()
{
}
FollowHandler::FollowHandler(Handler *next)
	: Handler(next)
{
}

bool FollowHandler::canHandle(const std::string &cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::string followerName;
	std::string followingName;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet *> output;
	std::getline(instr, line);

	std::stringstream ss(line); //FOLLOW John Carlos
	ss >> followerName;
	ss >> followingName;
	std::map<std::string, User *> copyUsers = eng->getUsers();
	if (copyUsers.find(followerName) == copyUsers.end())
	{
		std::cout << "addFollow() " << followerName << " is not a current user" << std::endl;
	}
	else if (copyUsers.find(followingName) == copyUsers.end())
	{
		std::cout << "addFollow() " << followingName << " is not a current user" << std::endl;
	}
	else
	{
		User *following = eng->getUsers().find(followingName)->second;
		eng->getUsers().find(followerName)->second->addFollowing(following);
		//std::cout << followerName << " is Following " << followingName << endl;
	}

	return HANDLER_OK;
}

QuitHandler::QuitHandler()
{
}

QuitHandler::QuitHandler(Handler *next)
	: Handler(next)
{
}

bool QuitHandler::canHandle(const std::string &cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng *eng, std::istream &instr) const
{
	eng->dumpMentions();
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{
}
AndHandler::AndHandler(Handler *next) : Handler(next)
{
}

bool AndHandler::canHandle(const std::string &cmd) const
{
	return cmd == "AND";
}
Handler::HANDLER_STATUS_T AndHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::string word;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet *> output;
	std::getline(instr, line);

	std::stringstream ss(line);

	while (ss >> word)
	{
		terms.push_back(word);
	}
	output = eng->search(terms, 0);
	displayHits(output);

	return HANDLER_OK;
}

OrHandler::OrHandler()
{
}
OrHandler::OrHandler(Handler *next) : Handler(next)
{
}

bool OrHandler::canHandle(const std::string &cmd) const
{
	return cmd == "OR";
}
Handler::HANDLER_STATUS_T OrHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::string word;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet *> output;
	std::getline(instr, line);

	std::stringstream ss(line);

	while (ss >> word)
	{
		terms.push_back(word);
	}
	output = eng->search(terms, 1);
	displayHits(output);

	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{
}
TweetHandler::TweetHandler(Handler *next) : Handler(next)
{
}

bool TweetHandler::canHandle(const std::string &cmd) const
{
	return cmd == "TWEET";
}
Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng *eng, std::istream &instr) const
{

	std::string word;
	std::string line;
	std::string tweet;
	std::string name;
	std::vector<string> terms;
	std::vector<Tweet *> output;
	std::getline(instr, line);
	std::stringstream ss(line);
	ss >> name;

	std::map<string, User*> copyUsers = eng->getUsers();
	if(copyUsers.find(name)==copyUsers.end()){
		return HANDLER_OK;
	}

	while (ss >> word)
	{
		tweet += " " + word;
	}
	tweet = tweet.substr(1, tweet.length());

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int year = timeinfo->tm_year;
	year += 1900;

	DateTime dt(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, year, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	eng->addTweet(name, dt, tweet);

	return HANDLER_OK;
}
