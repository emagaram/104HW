#include <iostream>
#include <iomanip>
#include "str.h"
using namespace std;

int main()
{
  Str sblank;
  const Str sref("World");
  Str s0("!");
  Str s1("Small");
  Str s1_copy(s1);
  
  cout << "sblank=" << sblank << endl;
  cout << "s1=" << s1 << endl;
  cout << "s1_copy=" << s1_copy << endl;

  cout << s1 + sref + s0 << endl;
  cout << s1 + " world" + s0 << endl;

  s1 += sref;
  s1 += "!";

  cout << s1 << endl;
  
  s0 = s1 = sref;
  cout << "s0 and s1 should be equal to \"World\". Actual values: " << s0 << " " << s1 << endl;
  s0 = s1 = "hello world";
  cout << "s0 and s1 should be equal to \"hello world\". Actual values: " << s0 << " " << s1 << endl;

  cout << s1 << " has size " << s1.size() << endl;

  s1[0] = 'H';
  s1[6] = 'W';

  cout << s1 << endl;

  cout << "The first letter of sref is " << sref[0] << endl;

  s1 = "Hello";
  Str s2("He");
  Str s3("Jello");
  cout << "Is " << s1 << " == " << s2 << "? " << boolalpha << (s1 == s2) << endl;
  cout << "Is " << s1 << " != " << s2 << "? " << boolalpha << (s1 != s2) << endl;
  cout << "Is " << s1 << " != " << s1 << "? " << boolalpha << (s1 != s1) << endl;
  cout << "Is " << s1 << " < " << s2 << "? " << boolalpha << (s1 < s2) << endl;
  cout << "Is " << s1 << " < " << s3 << "? " << boolalpha << (s1 < s3) << endl;
  cout << "Is " << s1 << " > " << s2 << "? " << boolalpha << (s1 > s2) << endl;
  cout << "Is " << s1 << " > " << s3 << "? " << boolalpha << (s1 > s3) << endl;

  cout << "Enter a string: " << endl;
  cin >> s1;
  cout << "You entered: " << s1 << endl;

  return 0;
}

