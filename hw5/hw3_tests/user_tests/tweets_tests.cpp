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
#include "../../user.h"
#include "../../datetime.h"
#include "../../tweet.h"



#undef private
#undef protected

// Attempt to add a blank Tweet to the User's Tweets
TEST(Tweets, BlankTweet) 
{
	User* a = new User("Chaplin"); 

	a->addTweet(new Tweet(a, DateTime(), std::string(""))); 

	std::list<Tweet*> tweets = a->tweets(); 

	delete a; 

	EXPECT_EQ(tweets.size(), 1) << "Expected user to have 1 Tweet, but instead has " << tweets.size(); 
	for(auto i : tweets) delete i;
}

// Attempt to add a relatively standard Tweet to the User's Tweets
TEST(Tweets, NormalTweet)
{
	User* a = new User("Keanu"); 

	a->addTweet(new Tweet(a, DateTime(), std::string("You're all #breathtaking!"))); 

	std::list<Tweet*> tweets = a->tweets(); 

	delete a; 

	EXPECT_EQ(tweets.size(), 1) << "Expected user to have 1 Tweet, but instead has " << tweets.size();
	for(auto i : tweets) delete i;
}

// Add a number of diversely styled Tweets to the User's Tweets
TEST(Tweets, ListTweets)
{
	User* a = new User("Jim_and_Dwight");

	a->addTweet(new Tweet(a, DateTime(), std::string("What kind of #bear is best?"))); 
	a->addTweet(new Tweet(a, DateTime(), std::string("Fact: Bears eat #beets"))); 
	a->addTweet(new Tweet(a, DateTime(), std::string("#Bear. #Beets. #Battlestar #Galactica"))); 
	a->addTweet(new Tweet(a, DateTime(), std::string("#Identity #theft is a #crime!"))); 
	a->addTweet(new Tweet(a, DateTime(), std::string("Millions of #families #suffer every year!"))); 

	std::list<Tweet*> tweets = a->tweets(); 

	delete a; 

	EXPECT_EQ(tweets.size(), 5) << "Expected user to have 1 Tweet, but instead has " << tweets.size(); 
	for(auto i : tweets) delete i;
}
