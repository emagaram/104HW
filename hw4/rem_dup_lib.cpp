#include "rem_dup_lib.h"

// Deletes consecutive equal values from the list
void removeConsecutive(Item *head)
{
    if (head->next != nullptr)
    {
        if (head->next->val == head->val)
        {
            Item *temp = head->next->next;
            delete head->next;
            head->next = temp;
        }
        if (head->next != nullptr)
        {
            removeConsecutive(head->next);
        }
    }
}

// Makes a copy of the items in the head1 and head2 lists
// concatenating the new head2 items to the end of the
// new head1 list items.
Item *concatenate(Item *head1, Item *head2)
{

    Item* cop1 = copy(head1);
    Item* cop2 = copy(head2);
    getTail(cop1)->next=cop2;
    return cop1;
}

Item* copy(Item *head){
    if(head->next!=nullptr){
        return new Item(head->val, copy(head->next));
    }
    else{
        return new Item(head->val,nullptr);
    }
}

Item* getTail(Item* head){
    if(head->next!=nullptr){
        return getTail(head->next);
    }
    else{
        return head;
    }
}