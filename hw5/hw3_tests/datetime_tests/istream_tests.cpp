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

// Attempt to read in a properly formatted DateTime
TEST(IStream, ProperFormat) 
{
	std::stringstream ss; 
	ss.str("2019-06-04 03:07:00"); 

	DateTime d; 

	ss >> d; 

	int sum = d.year + d.month + d.day + d.hour + d.min + d.sec; 

	EXPECT_EQ(sum, 2039) << "Expected for the DateTime object to have the values 2019-06-04 03:07:00"; 
}

// Attempt to read in an improperly formatted DateTime
// The program should assign the values to be the current system time
TEST(IStream, ImproperFormat)
{
	std::stringstream ss; 
	ss.str("2019-06:04 030700"); 

	DateTime d; 

	ss >> d; 

	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	int sum = d.year + d.month; 

	EXPECT_EQ(sum, timeinfo->tm_year + 1900 + timeinfo->tm_mon + 1) << "Expected for the DateTime object to be set to the current system time"; 
}