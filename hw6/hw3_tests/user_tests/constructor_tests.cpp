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

#define private public
#define protected public

#include "../../util.h"
#include "../../user.h"



#undef private
#undef protected

// Constructs a User with a blank string as the provided username 
// TEST(Constructor, BlankString)
// {
// 	std::string name = ""; 	
// 	User u(name); 

// 	if (u.name() != "") return testing::AssertionFailure() << "User's name does not match name assigned, which was an empty string"; 
// 	if (u.followers().size() != 0) return testing::AssertionFailure() << "followers().size() is not zero"; 
// 	if (u.following().size() != 0) return testing::AssertionFailure() << "following().size() is not zero"; 
// 	if (u.tweets().size() != 0) return testing::AssertionFailure() << "tweets().size() is not zero"; 
// 	if (getFeed().size() != 0) return testing::AssertionFailure() << "getFeed().size() is not zero"; 

// 	return testing::AssertionSuccess(); 
// }

// Constructs a User with a "normal" string as the provided username
TEST(Constructor, NormalString) 
{
	std::string name = "Mark Redekopp"; 	
	User u(name); 

	EXPECT_EQ(u.name(), "Mark Redekopp") << "User's name does not match name assigned, which was an empty string"; 
	EXPECT_EQ(u.followers().size(), 0) << "followers().size() is not zero"; 
	EXPECT_EQ(u.following().size(), 0) << "following().size() is not zero"; 
	EXPECT_EQ(u.tweets().size(), 0) << "tweets().size() is not zero"; 
	EXPECT_EQ(u.getFeed().size(), 0) << "getFeed().size() is not zero"; 

	testing::AssertionSuccess(); 
}