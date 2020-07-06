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
#include "../../datetime.h"

#undef private
#undef protected

// Test where the first DateTime is less than the second DateTime
TEST(DateTimeComparator, LessThanIsTrue) 
{

	DateTime early(12, 0, 0, 1999, 1, 10);
	DateTime late(12, 0, 0, 2000, 1, 10);

	EXPECT_TRUE(early < late) << "Expected true, returned false";

	
}

// Test where the first DateTime is greater than the second DateTime
TEST(DateTimeComparator, LessThanIsFalse) 
{

	DateTime early(12, 0, 0, 1999, 1, 10);
	DateTime late(12, 0, 0, 2000, 1, 10);

	EXPECT_FALSE(late < early) << "Expected false, returned true";

	
	
}

// Test where the first DateTime is equal to the second DateTime
TEST(DateTimeComparator, BothAreEqual) 
{

	DateTime early(12, 0, 0, 1999, 1, 10);
	DateTime late(12, 0, 0, 1999, 1, 10);

	EXPECT_FALSE(early < late) << "Expected false, returned true";

	
}