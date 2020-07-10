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
#include <stack>
#include <cstdlib>

TwitEng::TwitEng()
{
	_userCount = 0;
}

TwitEng::~TwitEng()
{
	std::set<Tweet *> allTweets;

	for (std::map<std::string, User *>::iterator usersIt = _users.begin(); usersIt != _users.end(); usersIt++)
	{
		User *userPtr = usersIt->second;
		std::vector<Tweet *> feed = userPtr->getFeed();

		for (std::vector<Tweet *>::iterator feedIt = feed.begin(); feedIt != feed.end(); feedIt++)
		{
			allTweets.insert(*feedIt);
		}
	}
	for (std::set<Tweet *>::iterator allTweetsIt = allTweets.begin(); allTweetsIt != allTweets.end(); allTweetsIt++)
	{
		delete *allTweetsIt;
	}

	for (std::map<std::string, User *>::iterator usersIt = _users.begin(); usersIt != _users.end(); usersIt++)
	{
		delete usersIt->second;
	}
}

void TwitEng::dfs(User *u, std::stack<User *> &stack_, std::map<User *, bool> &onStack, std::map<User *, int> &ids, std::map<User *, int> &low, int &id, int &sccCount)
{
	stack_.push(u);
	onStack.find(u)->second = true;
	low.find(u)->second = id++;
	ids.find(u)->second = low.find(u)->second;
	std::set<User *> followingCopy = u->following();

	for (std::set<User *>::iterator followIt = followingCopy.begin(); followIt != followingCopy.end(); followIt++)
	{
		if (ids.find(*followIt)->second == -1)
		{
			TwitEng::dfs(*followIt, stack_, onStack, ids, low, id, sccCount);
		}
		if (onStack.find(*followIt)->second)
		{
			low.find(u)->second = std::min(low.find(*followIt)->second, low.find(u)->second);
		}
	}
	if (ids.find(u)->second == low.find(u)->second)
	{
		while (!stack_.empty())
		{
			User *user = stack_.top();
			stack_.pop();
			onStack.find(user)->second = false;
			low.find(user)->second = ids.find(u)->second;
			if (user == u)
			{
				break;
			}
		}
		sccCount++;
	}
}

std::map<User *, int> TwitEng::findSCCs()
{
	std::map<User *, int> ids; //Id of each node
	std::map<User *, int> low; //Lowlink val of each node
	std::map<User *, bool> onStack;

	//Initializing for loop
	for (std::map<std::string, User *>::iterator userIt = _users.begin(); userIt != _users.end(); userIt++)
	{
		User *u = userIt->second;
		ids.insert(std::make_pair(u, -1));
		low.insert(std::pair<User *, int>(u, 0));
		onStack.insert(std::pair<User *, bool>(u, false));
		//std::pair<std::string, std::set<Tweet *>>(word, mentionTweets)
	}
	int idNum = 0;
	int sccCounter = 0;

	std::stack<User *> stack_;
	//Visits all unvisited nodes
	for (std::map<std::string, User *>::iterator userIt = _users.begin(); userIt != _users.end(); userIt++)
	{
		if (ids.find(userIt->second)->second == -1)
		{
			User *temp = userIt->second;
			dfs(temp, stack_, onStack, ids, low, idNum, sccCounter);
		}
	}
	return low;
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
	try
	{
		_userCount = std::stoi(userCount);
	}
	catch (const std::exception &e)
	{
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
	int month = std::stoi(line.substr(5, 2));
	int day = std::stoi(line.substr(8, 2));
	int hour = std::stoi(line.substr(11, 2));
	int min = std::stoi(line.substr(14, 2));
	int sec = std::stoi(line.substr(17, 2));
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

	for (std::set<Tweet *>::iterator s1Value = s1.cbegin(); s1Value != s1.cend(); ++s1Value)
	{
		answer.insert(*s1Value);
	}
	for (std::set<Tweet *>::iterator s2Value = s2.cbegin(); s2Value != s2.cend(); ++s2Value)
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
		std::map<std::string, std::set<Tweet *>>::iterator it = _hashTagIndex.find(terms[i]);
		if (it != _hashTagIndex.end())
		{
			//std::map<std::string, std::set<Tweet *>>::iterator it = _hashTagIndex.find(terms[i]); //log size of HTI which is logn
			std::set<Tweet *> *tweetsWithHT = &it->second;
			//TODO Cleanup
			if (i == 0 && strategy == 0)
			{
				result = *tweetsWithHT;
			}
			else if (strategy == 1)
			{
				result = result | *tweetsWithHT;
			}
			else
			{
				result = result & *tweetsWithHT;
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
