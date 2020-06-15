#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "user.cpp"

User *a;
DateTime youngest(10, 10, 10, 2010, 10, 10);
DateTime middle(10, 10, 10, 2011, 10, 10);
DateTime oldest(10, 10, 10, 2012, 10, 10);
DateTime superOld(10,10,10, 2013, 10,10);
Tweet t0(a, superOld, "hi");
Tweet t1(a, oldest, "hi");
Tweet t2(a, middle, "hi");
Tweet t3(a, youngest, "hi");


TEST_CASE("Merge 1 tweet to empty result returns true")
{
    std::list<Tweet *> result;
    std::list<Tweet*> add;
    add.push_back(&t3);
    mergeTweets(result, add);
    CHECK(*result.begin()==&t3);
    
}

TEST_CASE("Merge tweets in order test returns true")
{
    
    std::list<Tweet*> result;
    std::list<Tweet*> add;
    result.push_back(&t1);
    add.push_back(&t3);
    add.push_front(&t2);
    add.push_front(&t0);

    //0, 2, 1, 3 order

    mergeTweets(result, add);
    std::vector<Tweet*> vec(result.begin(),result.end());
    CHECK(result.back()==&t0);
    //CHECK(==&t2);
    //CHECK(==&t1);
    //CHECK(*result.begin()==&t3);
    //CHECK(.size()==4);

    


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