#include <fstream>
#include <iostream>
#include <sstream>
#include "rem_dup_lib.h"

void deleteLL(Item* head){
        while(head!=nullptr){
            Item* copy = head->next;
            delete head;
            head=copy;
        }    
}

std::string reverseString(std::string input)
{

    //I know there was a definiton for this in the lecture slides
    //I'm lazy lol
    std::string output = "";
    for (unsigned int i = 0; i < input.size(); i++)
    {
        //char c = input[input.size() - i - 1]; Works when running but segfault on debug
        output += std::string(1, input[input.size() - i - 1]);
    }
    return output;
}
Item *readAndCreateList(std::ifstream &iFile)
{
    std::string line;
    std::string word;
    std::getline(iFile, line);
    std::string reverse = reverseString(line); //O(N)
    std::stringstream ss(reverse);
    Item *head = nullptr;

    //Reads a reversed string of nums so that the LL
    //items can be made
    while (ss >> word)
    { //O(n)
        int val = std::stoi(word);
        head = new Item(val, head);
    }
    return head;
}



int main(int argc, char *argv[])
{
    std::ifstream iFile(argv[1]);
    if(iFile.fail()){
        std::cout << "File doesn't exist" << std::endl;
        return 0;
    }
    std::ofstream oFile(argv[2]);
    Item *head1 = readAndCreateList(iFile);
    removeConsecutive(head1);
    Item *head2 = readAndCreateList(iFile);
    Item *final = concatenate(head1, head2);
    Item* finalHead = final;
    //prints out final list
    while (final != nullptr)
    {
        oFile << final->val;
        if (final->next != nullptr)
        {
            oFile << " "; //Eliminates space at end
        }
        final = final->next;
    }
    deleteLL(finalHead);
    deleteLL(head1);
    deleteLL(head2);
}