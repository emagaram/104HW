#ifndef LLITER_H
#define LLITER_H

// Item definition - do NOT change
struct Item {
    int val;
    Item* next;
    // Constructor for convenience of testing
    Item(int v, Item* n): val(v), next(n) {}
};

// Assuming the linked list referenced by the argument head is sorted in
// ascending order, remove the range of items whose values are between
// min and max [inclusive] and return the pointer to the head of that extracted
// list.
//
// The argument head should be updated to point at the head of the remaining
// items in the original list (i.e. those items that are outside the range).
//
// No memory may be allocated or deallocated.
// You may use helper functions and define them in lliter.cpp but your
// solution must run in O(n).
//
Item* extractRange(Item* &head, int min, int max);

#endif


