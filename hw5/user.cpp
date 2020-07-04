#include "user.h"
#include "tweet.h"
using namespace std;

User::User(std::string name)
{
  _name = name;
  //_tweets = new list<Tweet*>();
}

User::~User()
{
}

string User::name() const
{
  return _name;
}

set<User *> User::followers() const
{
  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  return _followers;
}

set<User *> User::following() const
{
  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  return _following;
}

list<Tweet *> User::tweets() const
{
  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  return _tweets;
}

void User::addFollower(User *u)
{
  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  _followers.insert(u);
  u->_following.insert(this);
}

void User::addFollowing(User *u)
{
  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  _following.insert(u);
  u->_followers.insert(this);
}
bool otherLessThan(const Tweet *a, const Tweet *other)
{
  if (other < a)
  {
    return true;
  }
  return false;
}
void User::addTweet(Tweet *t)
{
  _tweets.push_back(t);
  _tweets.sort(otherLessThan);
  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
}

vector<Tweet *> User::getFeed()
{
  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  list<Tweet *> resultList(_tweets);
  for (set<User *>::iterator userIt = _following.begin(); userIt != _following.end(); userIt++)
  {
    list<Tweet *> copy((*userIt)->tweets());
    //Go through copy and remove first @mentions if they dont follow each other
    list<Tweet *>::iterator copyIt = copy.begin();
    while (copyIt != copy.end())
    {
      bool deleted = false;
      if ((*copyIt)->getPrivateViewer() != nullptr)
      {
        //All these copies are needed so that the equalities will return correct booleans
        User *viewer = (*copyIt)->getPrivateViewer();
        std::set<User *> viewerFollowing = viewer->following();
        std::set<User *> thisFollowing = this->following();

        if (viewer != this || viewerFollowing.find(this) == viewerFollowing.end() ||
            thisFollowing.find(viewer) == thisFollowing.end())
        {
          deleted = true;
          list<Tweet *>::iterator temp = copyIt;
          temp++;
          copy.remove(*copyIt);
          copyIt = temp;
        }
      }
      if (!deleted)
      {
        copyIt++;
      }
    }

    resultList.merge(copy, otherLessThan);
    
  }
  vector<Tweet *> vec(resultList.begin(), resultList.end());
  resultList.erase(resultList.begin(), resultList.end());
  return vec;
}