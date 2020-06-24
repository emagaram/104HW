#ifndef PIAZZA_H
#define PIAZZA_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
// You may add additional headers here
#include <map>
#include <set>


// A single post that can form a linked list
struct Post {
  Post(const std::string& val, Post* nxt) : text(val), next(nxt)
  {
    std::string word;
    std::stringstream ss(text); 
    while(ss >> word){
      termIndex.insert(word);
    }
  }
  
  std::string text;
  Post* next;
  // You may add other data members here (recall they are public)
  std::set<std::string> termIndex;
};


// A linked list of posts with limited capabilities
// You MAY NOT ALTER THIS CLASS. IT IS COMPLETE.
class PostList {
 public:
  PostList() { size = 0; head = NULL; }
  ~PostList() {
    while(head) { Post* cursor = head->next; delete head; head = cursor; }
  }
  void push_front(const std::string& val){
    head = new Post(val, head);
    size++;
  }
 protected:
  size_t size;
  Post* head;
};

//
// You may choose the kind of inheritance and/or data members of this class
// as well as adding private helper functions if you so choose.

class Piazza : public PostList /* <choose kind of inheritance */{
 public:
  Piazza();  // Constructor
  ~Piazza(); // Destructor - Clean up any necessary memory
  /// Adds a new post with the given string and performs any preprocessing
  /// necessary to support case-sensitive searches for individual words.
  ///  @param[in] data - text of the post to add
  ///  @param[in] pinned - true if this post should be pinned
  /// Assuming n >> t, runs in O(log(n)) where
  /// n is the number of existing posts and t is the average words per post 
  void addPost(const std::string& data, bool pinned);

  /// Returns the number of posts that contains the given term in their index.
  /// To make your life easier, you may perform case-sensitive searches
  ///  so that no extra processing is needed.
  /// Runs in O(n*log(t)) where n is the number of posts and t is the number
  ///  words in each post.
  size_t numMatches(const std::string& term);
  
  /// Returns the text of the i-th most recent post (includes all posts,
  /// pinned or not).  Indexing is 0-based, so i=0 indicates the most
  /// recent post. If i is an invalid index, throw std::out_of_range.
  /// Runs in O(i) where is is the input argument.
  const std::string& getIthMostRecentPost(size_t i);
  
  /// Returns the text of the i-th most recent pinned post (and does
  /// not include non-pinned posts. Indexing is 0-based, so i=0
  /// indicates the most recent pinned post. 
  /// If i is an invalid index, throw std::out_of_range.
  /// Runs in O(i) where is is the input argument.
  const std::string& getIthMostRecentPinnedPost(size_t i);

 private:
  // Add appropriate data members
  // You may use `std::vector`, `std::set`, and `std::map`.
  // You may not use `std::list`. If you want a linked-list you will
  // need to use code provided or write code to manage it yourelf.
};


#endif

