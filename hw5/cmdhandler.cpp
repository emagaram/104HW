#include "cmdhandler.h"
#include "util.h"
#include <sstream>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

QuitHandler::QuitHandler()
{
}

QuitHandler::QuitHandler(Handler* next)
	: Handler(next)
{
}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{
}
AndHandler::AndHandler(Handler* next) : Handler(next)
{
}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";

}
Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::string word;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet*> output;
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
OrHandler::OrHandler(Handler* next) : Handler(next)
{
}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}
Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::string word;
	std::string line;
	std::vector<string> terms;
	std::vector<Tweet*> output;
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
TweetHandler::TweetHandler(Handler* next) : Handler(next)
{
}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}
Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{

	std::string word;
	std::string line;
	std::string tweet;
	std::string name;
	std::vector<string> terms;
	std::vector<Tweet*> output;
	std::getline(instr, line);
	std::stringstream ss(line);
	ss >> name;
	while (ss >> word)
	{
		tweet += " " + word;
	}
	tweet = tweet.substr(1, tweet.length());
	
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int year = timeinfo->tm_year;
	year += 1900;
	
	DateTime dt(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, year, timeinfo->tm_mon+1, timeinfo->tm_mday);
	eng->addTweet(name, dt, tweet);
	

	return HANDLER_OK;
}
