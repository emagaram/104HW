#include <iostream>
#include "lliter.h"

// You may add prototypes for helper functions here

Item *extractRange(Item *&head, int min, int max)
{
  Item* trueBegin = head;
  Item* before = nullptr;
  Item* after = nullptr;
  Item* extractStart;
  Item* extractEnd;
  while (head->next!=nullptr && min > head->val && before==nullptr)
  {
    if(head->next->val >=min){
      before=head;
    }
    head=head->next;
  }
  if(before==nullptr){
    //min was greater than whole list
    head=trueBegin;
    return NULL;
  }
  extractStart=head;
  while(head->next!=nullptr && head->val < max){    
    head=head->next;
  }
  extractEnd=head;

  after = extractEnd->next;
  extractEnd->next=nullptr;
  before->next=after;
  head = trueBegin;
  return extractStart;
}
