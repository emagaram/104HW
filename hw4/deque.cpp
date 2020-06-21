#include <iostream>
#include "deque.h"
int main()
{
    //IGNORE THIS FILE
    Deque<int> *d = new Deque<int>();
    d->push_back(5);
    d->pop_back();
    d->push_front(8);
    d->pop_back();
    std::cout << "Ended!";
}