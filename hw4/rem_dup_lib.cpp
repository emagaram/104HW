#include "rem_dup_lib.h"

// Deletes consecutive equal values from the list
void removeConsecutive(Item* head){
    if(head->next->val==head->val){
        Item* temp = head->next->next;
        delete head->next;
    }
}

// Makes a copy of the items in the head1 and head2 lists
// concatenating the new head2 items to the end of the
// new head1 list items.
Item* concatenate(Item* head1, Item* head2){
    Item* b;
    return b;
}