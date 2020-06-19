#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rem_dup_lib.h"
#include <string>

TEST_CASE("Copy LL"){
    Item *d = new Item(3, nullptr);
    Item *c = new Item(2, d);
    Item *b = new Item(1, c);
    Item *a = new Item(0, b);

    Item* cop = copy(a);

    CHECK(cop->val == 0);
    CHECK(cop->next->val==1);
    CHECK(cop->next->next->next->val==3);
    CHECK(cop!=a);
    CHECK(cop->next!=a->next);
}

TEST_CASE("Concat 2 LinkedLists"){
    Item *d = new Item(1, nullptr);
    Item *c = new Item(1, d);
    Item *b = new Item(0, c);
    Item *a = new Item(0, b);

    Item* e = new Item(2, nullptr);
    Item* newHead = concatenate(a,e);
    CHECK(newHead->val==0);
    int i = 1;
    while(newHead->next!=nullptr){
        i++;
        newHead=newHead->next;
    }
    CHECK(i==5);
}

TEST_CASE("remove Consec Items 1 Item"){
    Item* a = new Item(101, nullptr);
    removeConsecutive(a);
    CHECK(a->val==101);
}

TEST_CASE("remove Consec 4 Items")
{

    Item *d = new Item(1, nullptr);
    Item *c = new Item(1, d);
    Item *b = new Item(0, c);
    Item *a = new Item(0, b);
    int actual[4] = {9, 9, 9, 9};
    removeConsecutive(a);
    Item *iterator = a;
    int i = 0;
    while (iterator != nullptr)
    {
        actual[i] = iterator->val;
        iterator = iterator->next;
        i++;
        if (iterator == nullptr)
        {
            break;
        }
    }
    CHECK(actual[0] == 0);
    CHECK(actual[1] == 1);
    CHECK(actual[2] == 9);
    CHECK(actual[3] == 9);
}