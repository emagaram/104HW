#include "twiteng.h"
#include <map>
#include <sstream>
#include <iostream>

TwitEng::TwitEng()
{
	_userCount = 0;
}

TwitEng::~TwitEng()
{
}

bool TwitEng::parse(char *filename)
{
	/**
 * Parses the Twitter database and populates internal structures
 * @param filename of the database file
 * @return true if there is an error, false if successful
 */
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
		if (userIt == _users.end())
		{
			centerUser = new User(word);
			_users.insert(std::pair<std::string, User *>(word, centerUser));
		}
		else
		{
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
	string line;
	std::getline(iFile, line);
	while (!iFile.eof())
	{
		if (line != "")
		{
			const DateTime dt = parseDate(line);
			const std::string txt = parseTweet(line);
			User *u = _users.find(parseName(line))->second;
			Tweet *t = new Tweet(u, dt, txt);

			u->addTweet(t);
		}
	std:
		getline(iFile, line);
	}

	iFile.close();
	return false;
}

DateTime TwitEng::parseDate(std::string line)
{
	int year = std::stoi(line.substr(0, 4));
	int month = std::stoi(line.substr(5, 6));
	int day = std::stoi(line.substr(8, 9));
	int hour = std::stoi(line.substr(11, 12));
	int min = std::stoi(line.substr(14, 15));
	int sec = std::stoi(line.substr(17, 18));
	DateTime dt(hour, min, sec, year, month, day);
	return dt;
}
std::string TwitEng::parseName(std::string line)
{
	line = line.substr(20, line.size() - 1);
	std::stringstream ss(line);
	std::string output;
	ss >> output;
	return output;
}
std::string TwitEng::parseTweet(std::string line)
{
	int length = parseName(line).size();
	return line.substr(20 + (length + 1), line.size() - 1);
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
	std::map<std::string, User *>::iterator userIt = _users.begin();
	while (userIt != _users.end())
	{
		User *u = userIt->second;
		std::string fname = u->name() += ".feed";
		ofstream ofile(fname);

		 	vector<Tweet*> feed = u->getFeed();
			sort(feed.begin(), feed.end(), TweetComp());
			int s = feed.size()-1;
			for(int i = 0; i<feed.size();i++){
				if(i==0){
					ofile<<u->name()<<std::endl;
				}
				ofile << *(feed[i]);
				if(i!=feed.size()-1){
					ofile << std::endl;
				}
			}
		userIt++;
			ofile.close();
	}
}
