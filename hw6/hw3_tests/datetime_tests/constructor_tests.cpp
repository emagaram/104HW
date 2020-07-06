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

// Test the default constructor
TEST(DateTimeConstructor, Default) 
{
	DateTime d;
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	int exp_year = 1900 + timeinfo->tm_year;
	int exp_month = timeinfo->tm_mon + 1;
	EXPECT_EQ(exp_year, d.year) << "Expected for the year " << exp_year;
	EXPECT_EQ(exp_month, d.month) << "Expected for the month " << exp_month;
}

// Test the overloaded constructor
TEST(DateTimeConstructor, Alt) 
{
	DateTime d(12, 12, 12, 1912, 12, 12);
	int sum = d.year + d.month + d.day + d.hour + d.min + d.sec; 

	EXPECT_EQ(sum, 1972) << "Expected for all DateTime values to be equal to 12"; 
}
