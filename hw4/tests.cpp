#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rem_dup_lib.h"
#include "deque.h"
#include <string>

TEST_CASE("Empty function")
{
    Deque<int> *e = new Deque<int>();
    CHECK(e->empty() == true);

    e->push_back(8);
    CHECK(e->empty() == false);
}

TEST_CASE("Deque Operator[]")
{
    Deque<int> *d = new Deque<int>();
    d->push_back(5);
    d->push_back(75);
    d->push_back(775);
    int a = (*d)[0];
    int b = (*d)[2];

    CHECK(a == 5);
    CHECK(b == 775);
    CHECK(d->size() == 3);
}

TEST_CASE("Deque Operator throws if out of bounds")
{
    Deque<int> *d = new Deque<int>();
    bool didThrow = false;
    try
    {
        (*d)[53];
    }
    catch (std::range_error &e)
    {
        didThrow = true;
    }
    CHECK(didThrow == true);
}

TEST_CASE("Pop front")
{
    Deque<int> *d = new Deque<int>();
    d->push_back(5);
    d->pop_front();
    CHECK(d->size() == 0);

    d->push_front(8);
    d->pop_front();
    CHECK(d->size() == 0);
}

TEST_CASE("Pop back")
{
    Deque<int> *d = new Deque<int>();
    d->push_back(5);
    d->pop_back();
    CHECK(d->size() == 0);

    d->push_front(8);
    d->pop_back();
    CHECK(d->size() == 0);
}

TEST_CASE("Push back on list with one item")
{
    Deque<int> *d = new Deque<int>();
    d->push_back(5);
    CHECK(d->size() == 1);
    CHECK((*d)[0] == 5);
}

TEST_CASE("Push front on list with one item")
{
    Deque<int> *d = new Deque<int>();
    d->push_front(5);
    CHECK(d->size() == 1);
    CHECK((*d)[0] == 5);
}

TEST_CASE("Copy Linked Lists")
{
    Item *d = new Item(3, nullptr);
    Item *c = new Item(2, d);
    Item *b = new Item(1, c);
    Item *a = new Item(0, b);

    Item *cop = copy(a);

    CHECK(cop->val == 0);
    CHECK(cop->next->val == 1);
    CHECK(cop->next->next->next->val == 3);
    CHECK(cop != a);
    CHECK(cop->next != a->next);
}

TEST_CASE("Concat 2 LinkedLists")
{
    Item *d = new Item(1, nullptr);
    Item *c = new Item(1, d);
    Item *b = new Item(0, c);
    Item *a = new Item(0, b);

    Item *e = new Item(2, nullptr);
    Item *newHead = concatenate(a, e);
    CHECK(newHead->val == 0);
    int i = 1;
    while (newHead->next != nullptr)
    {
        i++;
        newHead = newHead->next;
    }
    CHECK(i == 5);
}

TEST_CASE("remove Consec Items 1 Item")
{
    Item *a = new Item(101, nullptr);
    removeConsecutive(a);
    CHECK(a->val == 101);
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
