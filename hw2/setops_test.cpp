/**
 * Test file for setops: & | -
 */
#include <set>
#include <string>
#include <iostream>
#include "setops.h"
using namespace std;

// Prototype
std::ostream& operator<<(std::ostream& os, const std::set<std::string>& s);

// Make printing a set of strings easier
std::ostream& operator<<(std::ostream& os, const std::set<std::string>& s)
{
  for(std::set<std::string>::const_iterator it = s.begin();
      it != s.end();
      ++it)
    {
      os << *it << " ";
    }
  return os;
}

// Ensure ops will work on const sets
void const_func(const set<string>& s1, const set<string>& s2)
{
  cout << "Results: " << endl;
  set<string> s = s1 & s2;
  cout << s << endl;
  s = s1 | s2;
  cout << s << endl;
  s = s1 - s2;
  cout << s << endl;
}


int main()
{
  set<string> s1 = {"abc", "123", "def" };
  set<string> s2 = {"abc", "xyz" };

  const_func(s1, s2);
  
  return 0;
}
