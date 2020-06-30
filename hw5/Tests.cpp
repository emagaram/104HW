#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "user.cpp"
#include "twiteng.cpp"
#include "tweet.cpp"
User ez("ezra");
User *a = &ez;
User james("james");
User bob("bob");

DateTime y2010(10, 10, 10, 2010, 10, 10);
DateTime y2011(10, 10, 10, 2011, 10, 10);
DateTime y2012(10, 10, 10, 2012, 10, 10);
DateTime y2013(10, 10, 10, 2013, 10, 10);
Tweet t2013(a, y2013, "hi ezra!");
Tweet t2012(a, y2012, "hi");
Tweet t2011(a, y2011, "hi");
Tweet t2010(a, y2010, "hi");



TEST_CASE("Mention Index has right number of users"){
    TwitEng te;
    CHECK(te.getMentionIndex().size()==0);
    te.addTweet(ez.name(), y2013, "start #pac12 #Hi #FOOTbALL");
    te.addTweet(james.name(), y2010, "Sports! #fun #paC12");
    te.addTweet(james.name(), y2010, "This tweet should not increase index");
    CHECK(te.getMentionIndex().size()==2);
    te.addTweet(bob.name(), y2010, "This tweet should increase index");
    CHECK(te.getMentionIndex().size()==3); 

    TwitEng te2;
    string strfilename = "twitter.dat";
    char *filename = &strfilename[0];
    te2.parse(filename);
    CHECK(te2.getMentionIndex().size()==4);
}
TEST_CASE("Search AND"){
    TwitEng te;
    te.addTweet(ez.name(), y2013, "start #pac12 #Hi #FOOTbALL");
    te.addTweet(james.name(), y2010, "Sports! #fun #paC12");
    std::vector<std::string> searchTerms={"pac12","fun"};
    auto result = te.search(searchTerms, 0); 
    CHECK(result[0]->text()=="Sports! #fun #paC12");    
}

TEST_CASE("Search OR"){
    TwitEng te;
    te.addTweet(ez.name(), y2013, "start #pac12 #football #FOOTbALL");
    te.addTweet(james.name(), y2010, "Skydiving! #fun #YOLO");
    std::vector<std::string> searchTerms={"pac12"};

    auto result = te.search(searchTerms, 1); 
    CHECK(result[0]->text()=="start #pac12 #football #FOOTbALL");
    CHECK(result.size()==1);
    auto resultsHashtags = result[0]->hashTags();
    CHECK(resultsHashtags.find("pac12")!=resultsHashtags.end());
    CHECK(resultsHashtags.find("fakeHashtag")==resultsHashtags.end());
}

TEST_CASE("Hashtags in index map correctly"){
    TwitEng te;
    te.addTweet(ez.name(), y2013, "start #pac12 #football #FOOTbALL");
    te.addTweet(james.name(), y2010, "Skydiving! #fun #YOLO");
    std::map<std::string, User*> teUsers = te.getUsers();
    Tweet* ezraT = *(teUsers.find("ezra")->second->tweets().begin());
    Tweet* jamesT = *(teUsers.find("james")->second->tweets().begin());
    std::map<std::string, std::set<Tweet*>> hti = te.getHashTagIndex();
    CHECK(*(hti.find("pac12")->second.begin())==ezraT);
    CHECK(*(hti.find("fun")->second.begin())==jamesT);  
    CHECK(*(hti.find("pac12")->second.begin())!=jamesT);   
}


TEST_CASE("Add tweet updates users and hashTagIndex"){
    TwitEng te;
    te.addTweet(a->name(), y2013, "Can't wait for USC football to start #pac12 #football #FOOTbALL");
    std::map<std::string, User*> teUsers = te.getUsers();
    std::map<std::string, std::set<Tweet*>> hti = te.getHashTagIndex();
    CHECK(teUsers.size()==1);
    CHECK(teUsers.find(a->name())!=teUsers.end());
    CHECK(hti.size()==2);
    CHECK(hti.find("football")!=hti.end());
    CHECK(hti.find("FOOTbALL")==hti.end());
    CHECK(hti.find("pac12")!=hti.end());
    CHECK(hti.find("fakehashtag")==hti.end());
}

TEST_CASE("Hashtags are case insensitive and not repeated in tweets"){ 
    Tweet tweet (a, y2010, "start #PAC12 #foOTBALl #FooTball #pac12");
    set<string> ht = tweet.hashTags();
    CHECK(ht.size()==2);
    CHECK(ht.find("pac12")!=ht.end());
    CHECK(ht.find("football")!=ht.end());
    CHECK(ht.find("fakeHashtag")==ht.end());
}

TEST_CASE("Hashtags are in tweets"){ 
    Tweet tweet (a, y2010, "Can't wait for USC football to start #pac12 #football #pac12");
    set<string> ht = tweet.hashTags();
    CHECK(ht.size()==2);
    CHECK(ht.find("pac12")!=ht.end());
    CHECK(ht.find("football")!=ht.end());
    CHECK(ht.find("fakeHashtag")==ht.end());
}

TEST_CASE("Add tweet")
{
    User john("John");
    john.addTweet(&t2012);
    john.addTweet(&t2010);
    john.addTweet(&t2013);
    john.addTweet(&t2011);
    // vector<Tweet*> vec = john.getFeed();

    auto feed = john.getFeed();
    vector<Tweet *> vec(feed.begin(), feed.end());
    CHECK(vec[0]==&t2010);
    CHECK(vec[1]==&t2011);
    CHECK(vec[2]==&t2012);
    CHECK(vec[3]==&t2013);
}

TEST_CASE("parse tweet")
{
    //Make parseTweet and parseName pulic to test!
    // string line1 = "2019-05-20 12:35:14 Mark #Selma was an excellent movie to remember the struggle for civil rights";
    // string parsed1 = parseTweet(line1);
    // string expected1 = "#Selma was an excellent movie to remember the struggle for civil rights";
    // CHECK(parsed1==expected1);

    // string line = "2019-05-21 10:30:27 Sam @";
    // string parsed = parseTweet(line);
    // string expected = "@";
    // CHECK(parsed==expected);
}

TEST_CASE("parse name")
{
    // //Make public to test!
    // string line = "2019-05-20 12:35:14 Mark #Selma was an excellent movie to remember the struggle for civil rights";
    // //Second line to test
    // string line1 = "2019-05-21 10:30:27 Sam @Mark when is the next World Cup? #football";
    // string name = parseName(line);
    // string name1 = parseName(line1);
    // CHECK(name=="Mark");
    // CHECK(name1=="Sam");
}

TEST_CASE("parse date")
{
    // //Make public to test!
    // string line = "2019-05-20 12:35:14 Mark #Selma was an excellent movie to remember the struggle for civil rights";
    // DateTime dt = parseDate(line);
    // CHECK(dt.day==20);
    // CHECK(dt.year==2019);
    // CHECK(dt.month==5);
    // CHECK(dt.min==35);
    // CHECK(dt.sec==14);
}


//SOMETHING WEIRD, fails sometimes
TEST_CASE("add all users and tweets to engine")
{
    TwitEng te;
    string strfilename = "twitter.dat";
    char *filename = &strfilename[0];
    CHECK(te.parse(filename) == false);
    map<string, User *> users = te.getUsers();
    CHECK(users.size() == 4);
    CHECK(users.find("Mark") != users.end());
    CHECK(users.find("Tommy") != users.end());
    CHECK(users.find("Jill") != users.end());
    CHECK(users.find("Sam") != users.end());
    CHECK(users.find("Steve") == users.end());
    CHECK(users.find("Mark")->second->following().size() == 2);
    CHECK(users.find("Jill")->second->following().size() == 1);

    User *jill = users.find("Jill")->second;
    User *tommy = users.find("Tommy")->second;
    CHECK(tommy->tweets().size() == 0);
    CHECK(jill->tweets().size() == 2);

}

TEST_CASE("convert two digit int function")
{
    int oneDig = 5;
    int twoDig = 89;
    int threeDig = 129;
    std::string a = convertTwoDigitInt(oneDig);
    std::string b = convertTwoDigitInt(twoDig);
    std::string c = convertTwoDigitInt(threeDig);

    CHECK(a == "05");
    CHECK(b == "89");
    CHECK(c == "129");
}

TEST_CASE("output stream tweet with one digit values returns correctly")
{
    User ez("ezra");
    DateTime dt(1, 2, 3, 999, 5, 3);
    Tweet tweet(&ez, dt, "hi");
    std::stringstream buffer;
    buffer << tweet;
    std::string expectedOutput = "0999-05-03 01::02::03 ezra hi";
    std::string actualOutput = buffer.str();
    CHECK_EQ(actualOutput, expectedOutput);
}

TEST_CASE("output stream tweet returns hi ezra   !")
{
    //int hh, int mm, int ss, int year, int month, int day
    //string word;  YYYY-MM-DD HH::MM::SS username tweet_text
    std::stringstream buffer;
    buffer << t2013;
    std::string expectedOutput = "2013-10-10 10::10::10 ezra hi ezra!";
    std::string actualOutput = buffer.str();
    CHECK_EQ(actualOutput, expectedOutput);
}
TEST_CASE("User feed both empty lists")
{
    User joe("joe");
    User bob("bob");

    joe.addFollowing(&bob);
    vector<Tweet *> vec = joe.getFeed();
    CHECK_EQ(vec.size(), 0);
}

TEST_CASE("User Feed from empty list in ascending order")
{
    User joe("joe");

    User bob("bob");
    bob.addTweet(&t2012);
    bob.addTweet(&t2011);

    bob.addFollowing(&joe);
    vector<Tweet *> vec = bob.getFeed();
    vec = bob.getFeed();
    vec = bob.getFeed(); // twice in case messing with it
    CHECK_EQ(vec[0], &t2011);
    CHECK_EQ(vec[1], &t2012);
}

TEST_CASE("User follow(er)/(ing) correct ")
{
    User joe("joe");
    User steve("steve");

    User bob("bob");
    //bob follows joe and steve
    //joe follows bob
    //steve follows no one
    joe.addFollowing(&bob);
    bob.addFollowing(&joe);
    bob.addFollowing(&steve);
    CHECK(steve.followers().find(&bob) != steve.followers().end());
    CHECK(steve.followers().find(&steve) != steve.followers().end());
    CHECK(steve.followers().size() == 1);
    CHECK(joe.followers().size() == 1);
    CHECK(joe.following().size() == 1);
    CHECK(steve.following().size() == 0);
}

TEST_CASE("User Feed produces list in ascending order")
{
    User joe("joe");
    joe.addTweet(&t2013);
    joe.addTweet(&t2010);

    User bob("bob");
    bob.addTweet(&t2012);
    bob.addTweet(&t2011);

    bob.addFollowing(&joe);
    vector<Tweet *> vec = bob.getFeed();
    vec = bob.getFeed();
    vec = bob.getFeed(); // twice in case messing with it
    CHECK_EQ(vec[0], &t2010);
    CHECK_EQ(vec[1], &t2011);
    CHECK_EQ(vec[2], &t2012);
    CHECK_EQ(vec[3], &t2013);
}

TEST_CASE("Tweet list is sorted in ascending order")
{
    list<Tweet *> tweets;
    tweets.push_back(&t2012);
    tweets.push_back(&t2013);
    tweets.push_back(&t2010);
    tweets.push_back(&t2011);
    tweets.sort(otherLessThan);
    vector<Tweet *> vec(tweets.begin(), tweets.end());
    CHECK_EQ(vec[0], &t2010);
    CHECK_EQ(vec[1], &t2011);
    CHECK_EQ(vec[2], &t2012);
    CHECK_EQ(vec[3], &t2013);
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