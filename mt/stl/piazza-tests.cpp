#include "piazza.h"
#include <string>
using namespace std;

#include <gtest/gtest.h>


/*
 * Nominal test with values before and after defined range
 */
TEST(PiazzaNominal, AddBlankRegularPost)
{
  Piazza p;
  EXPECT_NO_THROW(p.addPost("", false));
}
TEST(PiazzaNominal, AddBlankPinnedPost)
{
  Piazza p;
  EXPECT_NO_THROW(p.addPost("", true));
}
TEST(PiazzaNominal, AddRegularPost)
{
  Piazza p;
  EXPECT_NO_THROW(p.addPost("word1", false));
}
TEST(PiazzaNominal, AddRegularPinnedPost)
{
  Piazza p;
  EXPECT_NO_THROW(p.addPost("word1", true));
}
TEST(PiazzaNominal, AddAndGetPosts)
{
  Piazza p;
  p.addPost("hello there", false);
  EXPECT_NO_THROW(p.getIthMostRecentPost(0));
  EXPECT_EQ("hello there", p.getIthMostRecentPost(0));
  p.addPost("bye bye", false);
  EXPECT_NO_THROW(p.getIthMostRecentPost(0));
  EXPECT_NO_THROW(p.getIthMostRecentPost(1));
  EXPECT_EQ("bye bye", p.getIthMostRecentPost(0));
  EXPECT_EQ("hello there", p.getIthMostRecentPost(1));
  p.addPost("nope yep hello", false);
  EXPECT_NO_THROW(p.getIthMostRecentPost(0));
  EXPECT_NO_THROW(p.getIthMostRecentPost(1));
  EXPECT_NO_THROW(p.getIthMostRecentPost(2));
  EXPECT_EQ("nope yep hello", p.getIthMostRecentPost(0));
  EXPECT_EQ("bye bye", p.getIthMostRecentPost(1));
  EXPECT_EQ("hello there", p.getIthMostRecentPost(2));

}

TEST(PiazzaNominal, NumMatches)
{
  Piazza p;
  p.addPost("hello there", false);
  p.addPost("bye bye", false);
  p.addPost("nope yep hello", false);
  EXPECT_EQ(2, p.numMatches("hello"));
  EXPECT_EQ(0, p.numMatches("Hello"));
}

TEST(PiazzaNominal, PinnedPosts)
{
  Piazza p;
  p.addPost("hello there", true);
  p.addPost("bye bye", false);
  p.addPost("nope yep hello", true);
  // Check that only the appropriate elements are in the pinned list
  EXPECT_EQ("nope yep hello", p.getIthMostRecentPinnedPost(0));
  EXPECT_EQ("hello there", p.getIthMostRecentPinnedPost(1));
  // Ensure the pinned list didn't interfere with the primary list
  EXPECT_EQ("nope yep hello", p.getIthMostRecentPost(0));
  EXPECT_EQ("bye bye", p.getIthMostRecentPost(1));
  EXPECT_EQ("hello there", p.getIthMostRecentPost(2));

}

