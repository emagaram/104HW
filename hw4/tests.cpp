#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rem_dup_lib.h"
#include <string>

    TEST_CASE("removeConsecutive")
    {
        Item* a;
        Item* b;
        Item* c;
        Item* d;
        a=new Item(0,b);
        b=new Item(0,c);
        c=new Item(1,d);
        d=new Item(1,nullptr);
        int actual[4] = {9,9,9,9};
        removeConsecutive(a);
        Item* iterator = a;
        int i = 0;
        while(iterator!=nullptr){
            actual[i] = iterator->val;
            iterator=iterator->next;
            i++;
        }
        CHECK(actual[0]==0);
        CHECK(actual[1]==19);
        CHECK(actual[2]==9);
        CHECK(actual[3]==9);
    }