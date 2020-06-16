#include "twiteng.h"
#include <map>
#include <sstream>

TwitEng::TwitEng()
{
	_userCount = 0;
}

TwitEng::~TwitEng()
{
}

bool TwitEng::parse(char *filename)
{
	std::ifstream iFile(filename);
	if (iFile.fail())
	{
		return true;
	}
	std::string oneWord;
	std::getline(iFile, oneWord);
	_userCount = std::stoi(oneWord);

	if (iFile.fail())
	{
		return true;
	}
	for (int i = 0; i < _userCount; i++)
	{
		std::string line;
		std::string word;
		std::getline(iFile, line);
		std::stringstream ss(line);
		ss >> word;
		User *centerUser; 

		//TODO cleanup
		std::map<std::string, User *>::iterator userIt = _users.find(word);
		if (userIt== _users.end())
		{
			centerUser= new User(word);
			_users.insert(std::pair<std::string, User *>(word, centerUser));
		}
		else{
			centerUser = userIt->second;
		}

		while (ss >> word)
		{
			User *u;
			std::map<std::string, User *>::iterator it = _users.find(word);
			if (it == _users.end())
			{
				u = new User(word);
				_users.insert(std::pair<std::string, User *>(word, u));
			}
			else
			{
				u = it->second;
			}

			centerUser->addFollowing(u);
		}
	}
	/**
 * Parses the Twitter database and populates internal structures
 * @param filename of the database file
 * @return true if there is an error, false if successful
 */
	return false;
}
std::map<std::string, User *> TwitEng::getUsers()
{
	return _users;
}

void TwitEng::addTweet(const std::string &username, const DateTime &time, const std::string &text)
{

	/**
 * Allocates a tweet from its parts and adds it to internal structures
 * @param username of the user who made the tweet
 * @param timestamp of the tweet
 * @param text is the actual text of the tweet as a single string
 */
}

std::vector<Tweet *> TwitEng::search(std::vector<std::string> &terms, int strategy)
{
	/**
 * Searches for tweets with the given words and strategy
 * @param words is the hashtag terms in any case without the '#'
 * @param strategy 0=AND, 1=OR
 * @return the tweets that match the search
 */
	return std::vector<Tweet *>();
}

void TwitEng::dumpFeeds()
{
}
