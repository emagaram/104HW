#include "setops.h"
#include <set>
#include <string>
using namespace std;

std::set<std::string> operator-(const std::set<std::string> &s1,
                                const std::set<std::string> &s2)
{
    set<string> answer;
    for (auto s1Value = s1.cbegin(); s1Value != s1.cend(); ++s1Value)
    {
        if (s2.find(*s1Value) == s2.end())
        {
            answer.insert(*s1Value);
        }
    }
    return answer;
}

std::set<std::string> operator|(const std::set<std::string> &s1,
                                const std::set<std::string> &s2)
{
    set<string> answer;
    for (auto s1Value = s1.cbegin(); s1Value != s1.cend(); ++s1Value)
    {
        answer.insert(*s1Value);
    }
    for (auto s2Value = s2.cbegin(); s2Value != s2.cend(); ++s2Value)
    {
        answer.insert(*s2Value);
    }
    return answer;
}
// Computes the intersection of s1 and s2
std::set<std::string> operator&(const std::set<std::string> &s1,
                                const std::set<std::string> &s2)
{
    set<string> answer;
    set<string> larger;
    set<string> smaller;
    if(s1.size()>s2.size()){
        larger = s1;
        smaller=s2;
    }
    else{
        larger=s2;
        smaller=s1;
    }
    for (auto largerValue = larger.cbegin(); largerValue != larger.cend(); ++largerValue)
    {
        if (smaller.find(*largerValue) != smaller.end())
        {
            answer.insert(*largerValue);
        }
    }
    return answer;
}