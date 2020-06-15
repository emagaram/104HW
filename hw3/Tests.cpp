#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "user.cpp"

User *a;
DateTime y2010(10, 10, 10, 2010, 10, 10);
DateTime y2011(10, 10, 10, 2011, 10, 10);
DateTime y2012(10, 10, 10, 2012, 10, 10);
DateTime y2013(10,10,10, 2013, 10,10);
Tweet t2013(a, y2013, "hi");
Tweet t2012(a, y2012, "hi");
Tweet t2011(a, y2011, "hi");
Tweet t2010(a, y2010, "hi");


TEST_CASE("User Feed produces list in ascending order"){
    User joe("joe");
    joe.addTweet(&t2013);
    joe.addTweet(&t2010);

    User bob("bob");
    bob.addTweet(&t2012);
    bob.addTweet(&t2011);

    bob.addFollowing(&joe);
    vector<Tweet*> vec = bob.getFeed();
    vec = bob.getFeed();
    vec = bob.getFeed(); // twice in case messing with it
    CHECK_EQ(vec[0],&t2010);
    CHECK_EQ(vec[1],&t2011);
    CHECK_EQ(vec[2],&t2012);
    CHECK_EQ(vec[3],&t2013);
}

TEST_CASE("Tweet list is sorted in ascending order"){
    list<Tweet*> tweets;
    tweets.push_back(&t2012);
    tweets.push_back(&t2013);
    tweets.push_back(&t2010);
    tweets.push_back(&t2011);
    tweets.sort(otherLessThan);
    vector<Tweet*> vec(tweets.begin(), tweets.end());
    CHECK_EQ(vec[0],&t2010);
    CHECK_EQ(vec[1],&t2011);
    CHECK_EQ(vec[2],&t2012);
    CHECK_EQ(vec[3],&t2013);
}


TEST_CASE("DateTime Less-Than Op returns true")
{
    DateTime a(10, 10, 10, 10, 10, 9);
    DateTime b(10, 10, 10, 10, 10, 10);
    CHECK((a < b) == true);
}

TEST_CASE("DateTime Less-Than Op returns false")
{
    DateTime a(10, 10, 10, 10, 10, 9);
    DateTime b(10, 10, 10, 10, 10, 10);
    CHECK((b < a) == false);
}

TEST_CASE("DateTime Less-Than Op returns true pt 2")
{
    DateTime a(10, 10, 10, 10, 10, 10);
    DateTime b(10, 9, 13, 10, 10, 10);
    CHECK((b < a) == true);
}

TEST_CASE("DateTime Less-Than Op returns false when equal")
{
    DateTime a(10, 10, 10, 10, 10, 10);
    DateTime b(10, 10, 10, 10, 10, 10);
    CHECK((a < b) == false);
}