#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "user.cpp"
#include "twiteng.cpp"
User ez("ezra");
User *a = &ez;

DateTime y2010(10, 10, 10, 2010, 10, 10);
DateTime y2011(10, 10, 10, 2011, 10, 10);
DateTime y2012(10, 10, 10, 2012, 10, 10);
DateTime y2013(10,10,10, 2013, 10,10);
Tweet t2013(a, y2013, "hi ezra!");
Tweet t2012(a, y2012, "hi");
Tweet t2011(a, y2011, "hi");
Tweet t2010(a, y2010, "hi");

TEST_CASE("add all users to engine"){
    TwitEng te;
    string strfilename = "twitter.dat";
    char* filename = &strfilename[0];
    CHECK(te.parse(filename)==false);
    map<string, User*> users = te.getUsers();
    CHECK(users.size()==4);
    CHECK(users.find("Mark")!=users.end());
    CHECK(users.find("Tommy")!=users.end());
    CHECK(users.find("Jill")!=users.end());
    CHECK(users.find("Sam")!=users.end());
    CHECK(users.find("Steve")==users.end());
    CHECK(users.find("Mark")->second->following().size()==2);
    CHECK(users.find("Jill")->second->following().size()==1);


}

TEST_CASE("convert two digit int function"){
    int oneDig = 5;
    int twoDig = 89;
    int threeDig = 129;
    std::string a = convertTwoDigitInt(oneDig);
    std::string b = convertTwoDigitInt(twoDig);
    std::string c = convertTwoDigitInt(threeDig);

    CHECK(a == "05");
    CHECK(b =="89");
    CHECK(c == "129");
}


TEST_CASE("output stream with one digit values returns correctly")
{
    User ez("ezra");
    DateTime dt(1, 2, 3, 999, 5, 3);
    Tweet tweet(&ez, dt, "hi");
    std::stringstream buffer;
    buffer << tweet;
    std::string expectedOutput = "0999-05-03 01::02::03 ezra hi";
    std::string actualOutput = buffer.str();
    CHECK_EQ(actualOutput,expectedOutput);
}

TEST_CASE("output stream returns hi ezra   !")
{
    //int hh, int mm, int ss, int year, int month, int day
    //string word;  YYYY-MM-DD HH::MM::SS username tweet_text
    std::stringstream buffer;
    buffer << t2013;
    std::string expectedOutput = "2013-10-10 10::10::10 ezra hi ezra!";
    std::string actualOutput = buffer.str();
    CHECK_EQ(actualOutput,expectedOutput);
}
TEST_CASE("User feed both empty lists"){
    User joe("joe");
    User bob("bob");

    joe.addFollowing(&bob);
    vector<Tweet*> vec = joe.getFeed();
    CHECK_EQ(vec.size(), 0);

}

TEST_CASE("User Feed from empty list in ascending order"){
    User joe("joe");

    User bob("bob");
    bob.addTweet(&t2012);
    bob.addTweet(&t2011);

    bob.addFollowing(&joe);
    vector<Tweet*> vec = bob.getFeed();
    vec = bob.getFeed();
    vec = bob.getFeed(); // twice in case messing with it
    CHECK_EQ(vec[0],&t2011);
    CHECK_EQ(vec[1],&t2012);
}


TEST_CASE("User follow(er)/(ing) correct "){
    User joe("joe");
    User steve("steve");

    User bob("bob");
    //bob follows joe and steve
    //joe follows bob
    //steve follows no one
    joe.addFollowing(&bob);
    bob.addFollowing(&joe);
    bob.addFollowing(&steve);
    CHECK(steve.followers().find(&bob)!=steve.followers().end());
    CHECK(steve.followers().find(&steve)!=steve.followers().end());
    CHECK(steve.followers().size()==1);
    CHECK(joe.followers().size()==1);
    CHECK(joe.following().size()==1);
    CHECK(steve.following().size()==0);


}

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