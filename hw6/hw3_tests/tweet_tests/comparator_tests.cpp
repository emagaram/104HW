#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#define private public
#define protected public


#include "../../util.h"
#include "../../tweet.h"
#include "../../datetime.h"
#include "../../user.h"

#undef private
#undef protected

// Test where the first Tweet is less than the second Tweet
TEST(TweetComparator, LessThanIsTrue) 
{
	User* a = new User("John");
	User* b = new User("Jane");

	DateTime e(12, 0, 0, 1999, 1, 10);
	DateTime l(12, 0, 0, 2000, 1, 10);

	Tweet early(a, e, "I am a generic person");
	Tweet late(b, l, "I, too, am a generic person");

	EXPECT_TRUE(early < late) << "Expected true, returned false";

	delete a;
	delete b;	
}

// Test where the first Tweet is greater than the second Tweet
TEST(TweetComparator, LessThanIsFalse) 
{
	User* a = new User("John");
	User* b = new User("Jane");

	DateTime e(12, 0, 0, 1999, 1, 10);
	DateTime l(12, 0, 0, 2000, 1, 10);

	Tweet early(a, e, "I am a generic person");
	Tweet late(b, l, "I, too, am a generic person");

	EXPECT_FALSE(late < early) << "Expected false, returned true";

	delete a;
	delete b;	
	
}

// Test where the first Tweet is equal to the second Tweet
TEST(TweetComparator, BothAreEqual) 
{
	User* a = new User("John");
	User* b = new User("Jane");

	DateTime e(12, 0, 0, 1999, 1, 10);
	DateTime l(12, 0, 0, 1999, 1, 10);

	Tweet early(a, e, "I am a generic person");
	Tweet late(b, l, "I, too, am a generic person");

	EXPECT_FALSE(early < late) << "Expected false, returned true";

	delete a;
	delete b;	
}