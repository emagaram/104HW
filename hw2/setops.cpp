//#include "setops.h"
#include <iostream>
#include <set>
#include <iterator>
using namespace std;


set<string> difference(set<string> a, set<string> b) {  
    set<string> answer;
    for(auto aValue=a.cbegin(); aValue != a.cend(); ++aValue){
        if(b.find(*aValue)==b.end()){
            answer.insert(*aValue);
        }
    }
    return answer;    
}


// Make printing a set of strings easier
void print(std::set<std::string> s)
{
  for(std::set<std::string>::const_iterator it = s.begin();
      it != s.end();
      ++it)
    {
      std::cout << *it << " ";
    }
}

void simpleDiffTest(){
    set<string> x = {"a", "b", "c", };
    set<string> y = {"a", "b", "c", "e"};
    set<string> expectedResult = {"a"};
    set<string> result = difference(x, y); 
    print(result);
}


int main()
{
    simpleDiffTest();     
    return 0;
}

