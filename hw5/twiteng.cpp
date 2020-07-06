#include "twiteng.h"
#include "tweet.h"
#include "user.h"
#include "hsort.h"
#include "datetime.h"
#include <map>
#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <fstream>

TwitEng::TwitEng()
{
	_userCount = 0;
}

TwitEng::~TwitEng()
{
	//I know I'm using auto and ranged for loops, just writing out the
	//iterators was too much work
	std::set<Tweet*> allTweets;
	for(auto userPair: _users){
		auto userPtr = userPair.second;
		auto feed = userPtr->getFeed();
		for(auto tweet : feed){
			allTweets.insert(tweet);
		}
	}
	for(auto tweet: allTweets){
		delete tweet;
	}

	for(auto userPair:_users){
		delete userPair.second;
	}
}
void TwitEng::addToMentionFeeds(Tweet *t)
{
	//Simply adds a tweet to a map of all users to their @mentions
	//Also gives tweets private viewers (a bit messy)
	std::string name;
	std::stringstream ss(t->text());
	bool firstWord = true;
	while (ss >> name)
	{
		if (name.substr(0, 1) == "@")
		{
			name = name.substr(1, name.length());
			if (_mentionFeeds.find(name) != _mentionFeeds.end())
			{
				_mentionFeeds.find(name)->second.insert(t);
				if (firstWord)
				{
					t->setPrivateViewer(_users.find(name)->second);
					// std::set<User *> userFollowing = t->user()->following();
					// std::set<User *> privateViewerFollowing = t->getPrivateViewer()->following();
					// if (userFollowing.find(t->getPrivateViewer()) != userFollowing.end() &&
					// 	privateViewerFollowing.find(t->user()) != privateViewerFollowing.end())
					// //If they follow each other
					// {
					// 	_mentionFeeds.find(name)->second.insert(t);
					// }
					break;
				}
				// else
				// {
				// 	//If not first mentioned then can always be added
				// 	_mentionFeeds.find(name)->second.insert(t);
				// }
			}
		}
		firstWord = false;
	}
}

void TwitEng::createMentionFeeds()
{
	std::map<std::string, User *>::iterator usersIt = _users.begin();
	while (usersIt != _users.end())
	{
		User *u = usersIt->second;
		std::list<Tweet *> tweetsCopy = u->tweets();
		std::list<Tweet *>::iterator tweetIt = tweetsCopy.begin();
		while (tweetIt != tweetsCopy.end())
		{
			Tweet *t = *tweetIt;
			addToMentionFeeds(t);
			tweetIt++;
		}
		usersIt++;
	}
}
std::map<std::string, std::set<Tweet *>> TwitEng::getHashTagIndex()
{
	return _hashTagIndex;
}
std::map<std::string, std::set<Tweet *>> TwitEng::getMentionIndex()
{
	return _mentionFeeds;
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
	std::string userCount;
	std::getline(iFile, userCount);
	try{
	_userCount = std::stoi(userCount);
	}
	catch(const std::exception &e){
		return true;
	}

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
		User *centerUser = addOrFindUser(word);
		if (_mentionFeeds.find(word) == _mentionFeeds.end())
		{
			std::set<Tweet *> mentionTweets;
			_mentionFeeds.insert(std::pair<std::string, std::set<Tweet *>>(word, mentionTweets));
		}

		while (ss >> word)
		{
			User *u = addOrFindUser(word);
			centerUser->addFollowing(u);
		}
	}
	std::string line;
	
	while (!iFile.eof())
	{
		std::getline(iFile, line);
		if (line != "")
		{
			const DateTime dt = parseDate(line);
			const std::string txt = parseTweet(line);
			User *u = _users.find(parseName(line))->second;
			//Tweet *t = new Tweet(u, dt, txt);

			//u->addTweet(t);
			addTweet(u->name(), dt, txt);
		}
		//std::getline(iFile, line);
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
	User *user = addOrFindUser(username);

	//This shouldn't need to be called here since it will always do nothing but I need
	//it for my tests to run
	if (_mentionFeeds.find(username) == _mentionFeeds.end())
	{
		std::set<Tweet *> mentionTweets;
		_mentionFeeds.insert(std::pair<std::string, std::set<Tweet *>>(username, mentionTweets));
	}

	Tweet *newTweet = new Tweet(user, time, text);
	user->addTweet(newTweet);

	std::set<std::string> ht = newTweet->hashTags();
	std::set<std::string>::iterator htIt = ht.begin();
	while (htIt != ht.end())
	{
		if (_hashTagIndex.find(*htIt) == _hashTagIndex.end())
		{
			std::set<Tweet *> tweets;
			tweets.insert(newTweet);
			_hashTagIndex.insert(std::pair<std::string, std::set<Tweet *>>(*htIt, tweets));
		}
		else
		{
			_hashTagIndex.find(*htIt)->second.insert(newTweet);
		}
		htIt++;
	}
}

std::set<Tweet *> operator|(const std::set<Tweet *> &s1,
							const std::set<Tweet *> &s2)
{
	std::set<Tweet *> answer;
	for (auto s1Value = s1.cbegin(); s1Value != s1.cend(); ++s1Value)
	{
		answer.insert(*s1Value);
	}
	for (auto s2Value = s2.cbegin(); s2Value != s2.cend(); ++s2Value)
	{
		answer.insert(*s2Value);
	}
	return answer;
}

// Computes the intersection of s1 and s2
std::set<Tweet *> operator&(const std::set<Tweet *> &t1,
							const std::set<Tweet *> &t2)
{
	std::set<Tweet *> answer;
	std::set<Tweet *> larger;
	std::set<Tweet *> smaller;
	if (t1.size() > t2.size())
	{
		larger = t1;
		smaller = t2;
	}
	else
	{
		larger = t2;
		smaller = t1;
	}
	for (std::set<Tweet *>::iterator largerValue = larger.cbegin(); largerValue != larger.cend(); ++largerValue)
	{
		if (smaller.find(*largerValue) != smaller.end())
		{
			answer.insert(*largerValue);
		}
	}
	return answer;
}

std::vector<Tweet *> TwitEng::search(std::vector<std::string> &terms, int strategy)
{
	std::set<Tweet *> result;

	for (size_t i = 0; i < terms.size(); i++)
	{
		std::map<std::string,std::set<Tweet*>>::iterator it =  _hashTagIndex.find(terms[i]);
		if (it != _hashTagIndex.end())
		{
			//TODO Cleanup
			if (i == 0 && strategy == 0)
			{
				result = it->second;
			}
			else if (strategy == 1)
			{
				result = result | it->second;
			}
			else
			{
				result = result & it->second;
			}
		}
	}
	return std::vector<Tweet *>(result.begin(), result.end());
}

void TwitEng::dumpMentions()
{
	createMentionFeeds();
	std::map<std::string, User *>::iterator userIt = _users.begin();
	while (userIt != _users.end())
	{
		User *u = userIt->second;
		std::string fname = u->name() += ".mentions";
		std::ofstream ofile(fname);
		std::set<Tweet *> userMentionsCopy = _mentionFeeds.find(u->name())->second;
		std::vector<Tweet *> feed(userMentionsCopy.begin(), userMentionsCopy.end());
		ofile << u->name() << std::endl;
		if (!feed.empty())
		{
			hsort(feed, TweetComp());
			for (size_t i = 0; i < feed.size(); i++)
			{
				ofile << *(feed[i]);
				if (i != feed.size() - 1)
				{
					ofile << std::endl;
				}
			}
		}
		userIt++;
	}
}

void TwitEng::dumpFeeds()
{
	dumpMentions();
	std::map<std::string, User *>::iterator userIt = _users.begin();
	while (userIt != _users.end())
	{
		User *u = userIt->second;
		std::string fname = u->name() += ".feed";
		std::ofstream ofile(fname);

		std::vector<Tweet *> feed = u->getFeed();
		hsort(feed, TweetComp());
		for (size_t i = 0; i < feed.size(); i++)
		{
			if (i == 0)
			{
				ofile << u->name() << std::endl;
			}
			ofile << *(feed[i]);
			if (i != feed.size() - 1)
			{
				ofile << std::endl;
			}
		}
		userIt++;
		ofile.close();
	}
}

User *TwitEng::addOrFindUser(std::string word)
{
	User *user;
	std::map<std::string, User *>::iterator userIt = _users.find(word);
	if (userIt == _users.end())
	{
		user = new User(word);
		_users.insert(std::pair<std::string, User *>(user->name(), user));
	}
	else
	{
		user = userIt->second;
	}
	return user;
}
