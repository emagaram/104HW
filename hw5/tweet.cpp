#include "tweet.h"
#include "datetime.h"
#include "util.h"
#include "user.h"
#include <sstream>
#include <string>
/**
   * Default constructor 
   */
Tweet::Tweet()
{
}

/**
   * Constructor 
   */
Tweet::Tweet(User *user, const DateTime &time, const std::string &text)
{
    _user = user;
    _dateTime = time;
    _text = text;

    std::string word;
    std::stringstream ss(text);
    while(ss >> word)
    {
        if (word.substr(0, 1) == "#")
        {
            word = word.substr(1, word.length());
            convLower(word);
            _hashTags.insert(word);
        }
    }
}

/**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
DateTime const &Tweet::time() const
{
    return _dateTime;
}

/**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
std::string const &Tweet::text() const
{
    return _text;
}

/**
   * Returns the hashtagged words without the '#' sign
   *
   */
std::set<std::string> Tweet::hashTags() const
{
    return _hashTags;
}

/**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
bool Tweet::operator<(const Tweet &other) const
{
    if (_dateTime < other._dateTime)
    {
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

std::string convertTwoDigitInt(int i)
{
    std::string s = "";
    if (i <= 9)
    {
        s += "0";
    }
    s += std::to_string(i);
    return s;
}

std::ostream &operator<<(std::ostream &os, const Tweet &t)
{
    DateTime dt = t.time();
    std::string yr = "";
    if (dt.year < 10)
    {
        yr += "000";
    }
    else if (dt.year < 100)
    {
        yr += "00";
    }
    else if (dt.year < 1000)
    {
        yr += "0";
    }
    yr += std::to_string(dt.year);

    os << yr << "-" << convertTwoDigitInt(dt.month) << "-" << convertTwoDigitInt(dt.day) << " "
       << convertTwoDigitInt(dt.hour) << "::" << convertTwoDigitInt(dt.min) << "::" << convertTwoDigitInt(dt.sec) << " ";
    
    os << t.user()->name() << " ";

    os << t.text();
    return os;
}

/* Create any other public or private helper functions you deem 
     necessary */

User *Tweet::user() const
{
    return _user;
}

/* You may add other member functions */
