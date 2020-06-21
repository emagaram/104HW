#include <iostream>
#include "deque.h"
int main(){
    Deque<int>* d = new Deque<int>();
    d->push_back(5);
    d->pop_back();
    //CHECK(d->size() == 0); 

    d->push_front(8);
    d->pop_back();
    //CHECK(d->size()==0);
    std::cout<<"Ended!";
}