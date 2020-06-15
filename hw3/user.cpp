#include "user.h"
#include "tweet.cpp" //Okay?
using namespace std;
void mergeTweets(std::list<Tweet*>& result, std::list<Tweet*>& add){
  //Assumes result is already in order

  //For increased speed if both lists are ordered, 
  //add in an iterator pointing to where last item was inserted

std::list<Tweet*>::iterator resIt;
std::list<Tweet*>::iterator addIt;

  for (addIt = add.begin(); addIt != add.end(); addIt++){
    for (resIt = result.begin(); resIt != result.end(); resIt++){
      if(  (*addIt)->time() < (*resIt)->time() ){
        //addIt goes on BEFORE resIt
        //std::list<Tweet*>::iterator prev = std::prev(resIt);
        result.insert(resIt, *addIt);
        break;
      }
      else if  (!((*resIt)->time() < (*addIt)->time()) && !((*addIt)->time() < (*resIt)->time())){
        //Equal time
        result.insert(resIt, *addIt); 
        break;
      }
      else if(resIt==result.end()){
        result.insert(resIt, *addIt);
      }
    }
  } 
}

int main(){
  
  cout <<"Hi";
}
User::User(std::string name)
{
  _name = name;
}

User::~User(){

}

string User::name() const{
    return _name;
}

set<User*> User::followers() const{
  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  return _followers;
}


set<User*> User::following() const{
      /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  return _following;
}

list<Tweet*> User::tweets() const{
  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */    
  return _tweets;
}

  void User::addFollower(User* u) {
  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  _followers.insert(u);
  }


void User::addFollowing(User* u){
 /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  _following.insert(u);
}

  void User::addTweet(Tweet* t){
  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */      
  }


vector<Tweet*> User::getFeed(){
  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */    
  vector<Tweet*> a;
  return a;
}  