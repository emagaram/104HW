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
#include <iostream>
#include <ctime>
#include <chrono>

#define private public
#define protected public

#include "../../util.h"
#include "../../user.h"


#undef private
#undef protected

// Attempt to add a new User to a User's following set
TEST(Following, NewUser) 
{
	User* a = new User("user"); 
	User* b = new User("other_user"); 
	User* c = new User("Surprise!_Another_user"); 

	a->addFollowing(b); 
	a->addFollowing(c); 

	std::set<User*> following = a->following(); 

	delete a; 
	delete b; 
	delete c; 

	EXPECT_EQ(2, following.size()) << "Expected to have 2 following, but actually have " << following.size(); 
}

// Attempt to add a User to a User's Following set twice
TEST(Following, UserAlreadyInSet)
{
	User* a = new User("user"); 
	User* b = new User("other_user"); 
	User* c = new User("Surprise!_Another_user"); 

	a->addFollowing(b); 
	a->addFollowing(c); 
	a->addFollowing(b); 
	a->addFollowing(c); 

	std::set<User*> following = a->following(); 

	delete a;
	delete b; 
	delete c; 

	EXPECT_EQ(2, following.size()) << "Expected to have 2 following, but actually have " << following.size(); 
}