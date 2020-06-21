#include "gtest\gtest.h"
#include "rem_dup_lib.h"
#include "deque.h"
#include <string>
namespace myDeque
{

    TEST(Deque, BunchOfFunctions)
    {
        Deque<int> e;
        EXPECT_EQ(e.empty(), true);
        e.push_back(8);
        e.push_back(9);
        e.push_front(7);
        e.pop_back();
        EXPECT_EQ(e.size(),2);
        EXPECT_EQ((e)[0],7);
        EXPECT_EQ((e)[1],8);
        e.pop_front();
        EXPECT_EQ((e)[0],8);
        e.pop_front();
        e.push_front(19);
        e.push_front(20);
        e.push_front(20);
        e.push_front(20);
        e.push_front(20);
        e.push_front(20);
        e.push_front(21);
        EXPECT_EQ(e.size(),7);
        EXPECT_EQ(e[6],19);
    }    
    TEST(Deque, EmptyFunction)
    {
        Deque<int> e;
        EXPECT_EQ(e.empty() , true);

        e.push_back(8);
        EXPECT_EQ(e.empty() , false);
    }

    TEST(Deque, DequeOperator)
    {
        Deque<int> d;
        d.push_back(5);
        d.push_back(75);
        d.push_back(775);
        int a = d[0];
        int b = d[2];

        EXPECT_EQ(a , 5);
        EXPECT_EQ(b , 775);
        EXPECT_EQ(d.size() , 3);
    }

    TEST(Deque, DequeOperatorThrowsIfOutOfBounds)
    {
        Deque<int> d;
        bool didThrow = false;
        try
        {
            d[53];
        }
        catch (std::range_error &e)
        {
            didThrow = true;
        }
        EXPECT_EQ(didThrow , true);
    }

    TEST(Deque, PopFront)
    {
        Deque<int> d;
        d.push_back(5);
        d.pop_front();
        EXPECT_EQ(d.size() , 0);

        d.push_front(8);
        d.pop_front();
        EXPECT_EQ(d.size() , 0);
    }

    TEST(Deque, PopBack)
    {
        Deque<int> d;
        d.push_back(5);
        d.pop_back();
        EXPECT_EQ(d.size() , 0);

        d.push_front(8);
        d.pop_back();
        EXPECT_EQ(d.size() , 0);
    }

    TEST(Deque, PushBackOnListWithOneItem)
    {
        Deque<int> d;
        d.push_back(5);
        EXPECT_EQ(d.size() , 1);
        EXPECT_EQ(d[0] , 5);
    }

    TEST(Deque, PushFrontOnListWithOneItem)
    {
        Deque<int> d;
        d.push_front(5);
        EXPECT_EQ(d.size() , 1);
        EXPECT_EQ(d[0] , 5);
    }

    TEST(Deque, CopyLinkedLists)
    {
        Item *d = new Item(3, nullptr);
        Item *c = new Item(2, d);
        Item *b = new Item(1, c);
        Item *a = new Item(0, b);

        Item *cop = copy(a);

        EXPECT_EQ(cop->val , 0);
        EXPECT_EQ(cop->next->val , 1);
        EXPECT_EQ(cop->next->next->next->val , 3);

        delete cop;
        delete a;
        delete b;
        delete c;
        delete d;
    }

    TEST(Deque, Concat2LinkedLists)
    {
        Item *d = new Item(1, nullptr);
        Item *c = new Item(1, d);
        Item *b = new Item(0, c);
        Item *a = new Item(0, b);

        Item *e = new Item(2, nullptr);
        Item *newHead = concatenate(a, e);
        EXPECT_EQ(newHead->val , 0);
        int i = 1;
        while (newHead->next != nullptr)
        {
            i++;
            newHead = newHead->next;
        }
        EXPECT_EQ(i , 5);
        delete a;
        delete b;
        delete c;
        delete d;
    }

    TEST(Deque, RemoveConsecItems1Item)
    {
        Item *a = new Item(101, nullptr);
        removeConsecutive(a);
        EXPECT_EQ(a->val , 101);
    }

    TEST(Deque, RemoveConsec4Items)
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
        EXPECT_EQ(actual[0] , 0);
        EXPECT_EQ(actual[1], 1);
        EXPECT_EQ(actual[2] , 9);
        EXPECT_EQ(actual[3] , 9);
        delete a;
        delete b;
        delete c;
        delete d;
    }

}
