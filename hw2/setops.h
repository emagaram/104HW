#ifndef SETOPS_H
#define SETOPS_H
#include <set>
#include <string>
    // Computes the intersection of s1 and s2
    std::set<std::string> operator&(const std::set<std::string>& s1, 
    const std::set<std::string>& s2);



    // Computes the union of s1 and s2
    std::set<std::string> operator|(const std::set<std::string>& s1, 
    const std::set<std::string>& s2);

    // Computes the difference of s1 - s2
    std::set<std::string> operator-(const std::set<std::string>& s1,
    const std::set<std::string>& s2); 
#endif
 



   