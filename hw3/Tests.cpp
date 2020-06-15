#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dateTime.cpp"

TEST_CASE("DateTime Less-Than Op returns true") {
    DateTime a (10,10,10,10,10,9);
    DateTime b (10,10,10,10,10,10);
    CHECK( (a<b) == true);
}

TEST_CASE("DateTime Less-Than Op returns false") {
    DateTime a (10,10,10,10,10,9);
    DateTime b (10,10,10,10,10,10);
    CHECK( (b<a) == false);
}

TEST_CASE("DateTime Less-Than Op returns true pt 2") {
    DateTime a (10,10,10,10,10,10);
    DateTime b (10,9,13,10,10,10);
    CHECK( (b<a) == true);
}

TEST_CASE("DateTime Less-Than Op returns false when equal") {
    DateTime a (10,10,10,10,10,10);
    DateTime b (10,10,10,10,10,10);
    CHECK( (a<b) == false);
}