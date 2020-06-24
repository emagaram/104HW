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
  Post* p = new Post(data, head,pinned);
  std::vector<std::string> words = makeWords(data);
  p->next=head;
  head=p;
  


  
}

// Complete the code below.
// Remember this must run in O(n*log(t)) where n is the number
// of posts and t is the number of words per post
size_t Piazza::numMatches(const std::string& term)
{
	Post* begin = head;
	size_t count = 0;

	while(begin!=nullptr){
		std::set<std::string> items = begin->termIndex;

		if(items.find(term)!=items.end()){
			count++;
		}
		begin = begin->next;
	}
}

// Complete the code below.
// Must run in O(i)
const std::string& Piazza::getIthMostRecentPost(size_t i)
{ 
	Post* it=head;
	size_t count = 0;
	while(count!=i){
		it=it->next;
		count++;
	}
	return it->text;
}

// Complete the code below.
// Must run in O(i)
const std::string& Piazza::getIthMostRecentPinnedPost(size_t i)
{
 
}

