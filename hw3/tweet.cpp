#include "tweet.h"
  /**
   * Default constructor 
   */
  Tweet::Tweet(){

  }

  /**
   * Constructor 
   */
  Tweet::Tweet(User* user, const DateTime& time, const std::string& text){
      _user = user;
      _dateTime = time;
      _text = text;
  }

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & Tweet::time() const{
      return _dateTime;
  }

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  std::string const & Tweet::text() const{
      return _text;      
  }

  /**
   * Returns the hashtagged words without the '#' sign
   *
   */
  std::set<std::string> Tweet::hashTags() const{
      return _hashTags;
  }

  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
  bool Tweet::operator<(const Tweet& other) const{
      if(_dateTime<other._dateTime){
          return true;
      }
      return false;
  }

  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
  

std::ostream& operator<<(std::ostream& os, const Tweet& t)
{
	return os;
}

  /* Create any other public or private helper functions you deem 
     necessary */

  User* Tweet::user() const{
      return _user;
  }

  /* You may add other member functions */

