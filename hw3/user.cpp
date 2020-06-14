#include "user.h"
#include <iostream>
using namespace std;

void mergeTweets(std::list<Tweet*> result, std::list<Tweet*> add){
  //Assumes result is already in order
std::list<Tweet*>::iterator resIt;
std::list<Tweet*>::iterator addIt = add.begin();
  for (resIt = result.begin(); resIt != result.end(); ++resIt){
      if(  (*addIt)->time() << (*resIt)->time() ){

      }
  } 
}

int main(){
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