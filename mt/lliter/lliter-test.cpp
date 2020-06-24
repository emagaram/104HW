#include <iostream>
#include <vector>
#include <cstdlib>
#include "lliter.h"
using namespace std;

// This code is complete (read the documentation for main below)


// Convenience functions to help you test your code if you like
void printList(Item* list);
void deleteList(Item* list);

// Will read all integers on the command line into a linked list
// e.g. ./lliter-test 2 5 7 11 will produce a linked list with 2 5 7 11
// and then call extractRange on that list using 10 and 20 (feel
// free to modify the min, max values of 10,20).
int main(int argc, char* argv[])
{
    Item* head = NULL;
    Item* curr;
    for(int i = 1; i < argc; i++) {
        if(i==1) head = curr = new Item(atoi(argv[i]), NULL);
        else {
            curr->next = new Item(atoi(argv[i]), NULL);
            curr = curr->next;
        }
    }

    cout << "Original list: " << endl;
    printList(head);

    Item *removed = extractRange(head,10,20);

    cout << "Remaining in original: " << endl;
    printList(head);
    cout << "Removed: " << endl;
    printList(removed);

    cout << "Cleaning up" << endl;
    deleteList(head);
    deleteList(removed);
    return 0;

}

void printList(Item* list) {
    Item * tmp = list;
    while(tmp != NULL) {
        cout << tmp->val << " ";
        tmp =tmp->next;
    }
    cout << endl;
}

void deleteList(Item* list) {
  if(list) {
    deleteList(list->next);
    delete list;
  }
}
