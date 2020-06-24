#include "piazza.h"
using namespace std;

// Helper function to convert a string of text to individual words
std::vector<std::string> makeWords(const std::string& s)
{
  std::vector<std::string> words;
  std::stringstream ss(s);
  std::string temp;
  while(ss >> temp){
    words.push_back(temp);
  }
  return words;
}

// Complete the constructor below as needed
Piazza::Piazza()
{

}

// Complete the destructor below as needed
Piazza::~Piazza()
{

}



// Runs in O(log(n)), assuming n >> t where n is the number  
// of existing posts and t is the number of words in the post.
void Piazza::addPost(const std::string& data, bool pinned)
{
  // You may change this line and add the remainder of your
  // implementation
  std::vector<std::string> words = makeWords(data);


  
}

// Complete the code below.
// Remember this must run in O(n*log(t)) where n is the number
// of posts and t is the number of words per post
size_t Piazza::numMatches(const std::string& term)
{


}

// Complete the code below.
// Must run in O(i)
const std::string& Piazza::getIthMostRecentPost(size_t i)
{

  
}

// Complete the code below.
// Must run in O(i)
const std::string& Piazza::getIthMostRecentPinnedPost(size_t i)
{

  
}

