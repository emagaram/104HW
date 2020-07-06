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

// Retrieve a User's feed when the User is not following anyone
TEST(Feed, NotFollowing) 
{
	User u("CS104_Student"); 
	std::vector<Tweet*> feed = u.getFeed(); 
	EXPECT_EQ(feed.size(), 0) << "The size of the feed should be zero, but is actually " << feed.size(); 
}

// TODO Retrieve a User's feed when User is following other Users that have no Tweets
TEST(Feed, FollowingButNoTweets) 
{
	User* a = new User("Tommy_Trojan"); 
	User* b = new User("Joe_Bruin"); 
	User* c = new User("Oski"); 

	a->addFollowing(b); 
	a->addFollowing(c); 

	std::vector<Tweet*> feed = a->getFeed(); 

	delete a; 
	delete b; 
	delete c; 
	
	EXPECT_EQ(feed.size(), 0) << "The size of the feed should be zero, but it is actually " << feed.size(); 
	for(auto i : feed ) delete i;
}

// Retrieve a User's feed that should be relatively small
TEST(Feed, Small) 
{
	User* a = new User("Tommy_Trojan"); 
	User* b = new User("joe_bruin"); 
	User* c = new User("oski"); 

	// User a should follow Users b and c
	a->addFollowing(b);
	a->addFollowing(c);

	a->addTweet(new Tweet(a, DateTime(), std::string("CS104 and CS170 are so easy!")));
	b->addTweet(new Tweet(b, DateTime(), std::string("CS104 homework is super hard!"))); 
	c->addTweet(new Tweet(c, DateTime(), std::string("CS170 homework is impossible!"))); 

	std::vector<Tweet*> feed = a->getFeed(); 

	delete a; 
	delete b; 
	delete c; 

	EXPECT_EQ(feed.size(), 3) << "The size of the feed should be two, but it is actually " << feed.size(); 
	for(auto i : feed ) delete i;
}

// TODO Retrieve a User's feed where not all of the followed Users have made tweets
TEST(Feed, Medium)
{
	User* a = new User("Tommy_Trojan"); 
	User* b = new User("joe_bruin"); 
	User* c = new User("oski"); 
	User* d = new User("harry_the_husky"); 
	User* e = new User("benny_beaver"); 

	// Add appropriate followers for each of the users. User* a will be the variable under test here
	a->addFollowing(b); 
	a->addFollowing(c); 
	a->addFollowing(d); 
	a->addFollowing(e); 

	a->addTweet(new Tweet(a, DateTime(), std::string("Fight On!"))); 
	b->addTweet(new Tweet(b, DateTime(), std::string("go bruins"))); 
	c->addTweet(new Tweet(c, DateTime(), std::string("go bears"))); 
	d->addTweet(new Tweet(d, DateTime(), std::string("bow down to washington"))); 
	e->addTweet(new Tweet(e, DateTime(), std::string("go beavs"))); 

	// Get User a's feed
	std::vector<Tweet*> feed = a->getFeed(); 

	delete a; 
	delete b; 
	delete c; 
	delete d; 
	delete e; 

	EXPECT_EQ(feed.size(), 5) << "The size of the feed should be five, but it is actually " << feed.size(); 
	for(auto i : feed ) delete i;
}

// Retrieve a User's feed that should be relatively large
TEST(Feed, Large) 
{
	User* a = new User("Mark_Redekopp"); 
	User* b = new User("Aaron_Cote"); 
	User* c = new User("Jeffrey_Miller"); 
	User* d = new User("Gandhi_Puvvada"); 
	User* e = new User("Andrew_Goodney"); 
	User* f = new User("CS_Student"); 
	User* g = new User("CECS_Student"); 
	User* h = new User("CSBA_Student"); 
	User* i = new User("Freshman"); 

	a->addTweet(new Tweet(a, DateTime(), std::string("For my next trick, I will now explain gate logic using a sock"))); 
	b->addTweet(new Tweet(b, DateTime(), std::string("It is always important to transform OPT into OPT(imus) prime"))); 
	c->addTweet(new Tweet(c, DateTime(), std::string("Don't forget to flush"))); 
	d->addTweet(new Tweet(d, DateTime(), std::string("Wasting clocks is a SIN"))); 
	e->addTweet(new Tweet(e, DateTime(), std::string("Today, we'll be learning about pointers!"))); 
	f->addTweet(new Tweet(f, DateTime(), std::string("Wow, 104 is one of the hardest classes I've ever had to take"))); 
	g->addTweet(new Tweet(g, DateTime(), std::string("Finally done with 354. 457 can't be that bad, right?"))); 
	h->addTweet(new Tweet(h, DateTime(), std::string("I can handle the business side and everything!"))); 
	i->addTweet(new Tweet(i, DateTime(), std::string("I'm so excited for four years of USC Computer Science!"))); 

	a->addFollowing(b); 
	a->addFollowing(c); 
	a->addFollowing(d); 
	a->addFollowing(e); 
	a->addFollowing(f); 
	a->addFollowing(g); 
	a->addFollowing(h); 
	a->addFollowing(i); 

	std::vector<Tweet*> feed = a->getFeed(); 

	delete a; 
	delete b; 
	delete c; 
	delete d; 
	delete e; 
	delete f; 
	delete g; 
	delete h; 
	delete i; 

	EXPECT_EQ(9, feed.size()) << "The size of the feed should be nine, but it is actually " << feed.size();

	for(auto i : feed ) delete i;
}
