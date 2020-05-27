//
// CS104 Heap test suite
//



// make public for access to internal data
#define private public
#define protected public

#include <str.h>

#undef private
#undef protected



#include <gtest/gtest.h>

#include <random_generator.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#define RANDOM_SEED 57821


/**
 * Check that the given strcontent
 */
testing::AssertionResult checkStrContents(const std::string& exp, const Str& actual)
{
	// sort vector least to greatest so that the order of elements matches the order in the heap
  if(actual.data_ == NULL){
    return testing::AssertionFailure() << "NULL pointer in data_ member of Str";
  }
  else if(0 != strcmp(exp.c_str(), actual.data_)){
    return testing::AssertionFailure() << "Content mismatch: expected: " << exp << " / actual: " << actual.data_;
  }
  return testing::AssertionSuccess();
}

TEST(StrTestConstructorTests, DefaultConstructor)
{
	Str s1;
	std::string exp = "";
	checkStrContents(exp, s1);
}

TEST(StrTestConstructorTests, CharArrayConstructor)
{
	Str s1("abc");
	std::string exp = "abc";
	checkStrContents(exp, s1);
}

TEST(StrTestConstructorTests, NullInputConstructor)
{
	Str s1(NULL); 
	// No great defined behavior for this, so just don't run into memory problems
}

TEST(StrTestConstructorTests, StrConstructor)
{
	Str s1("abc");
	Str s2(s1);
	
	s1 = "abcdef";
	std::string exp = "abc";
	checkStrContents(exp, s2);
}

TEST(StrTestOpAssign, AssignStr)
{
	Str s1("abc");
	Str s2("def");

	s1 = s2; 
  std::string exp = "def";
	EXPECT_EQ(exp, std::string(s1.data_)) << "Contents differ from expected, data incorrectly copied";
}

TEST(StrTestOpAssign, AssignSelf)
{
	Str s1("abc");
	s1 = s1;
	std::string exp = "abc";
	EXPECT_EQ(exp, std::string(s1.data_)) << "Contents differ from expected in assignment to self";
}

// TEST(StrTestOpAssign, NullData)
// {
// 	Str s1(NULL);
// 	Str s2("abc");
// 	// They need to check if data_ exists before deleting it
// 	s1 = s2; 
// 	std::string exp = "abc";
// 	EXPECT_EQ(exp, std::string(s1.data_));
// }

// TEST(StrTestOpAssign, AssignCharArrayToNull)
// {
// 	Str s1(NULL);
// 	char s2[4] = "abc";
// 	s1 = s2;
// 	checkStrContents(s2, s1);
// }

//Making sure they don't alter rhs

TEST(StrTestOpAssign, AssignCharArray)
{
	Str s1("abc");
	char s2[4] = "def";
	char s3[4] = "def";
	s1 = s2;
	std::string exp = "def";
	checkStrContents(exp, s1);
	EXPECT_EQ(std::string(s3), std::string(s2)); 
}

TEST(StrTestOpPlus, AddTwoStrings1)
{
  Str s1("abc");
  Str s2("def");
  std::string exp = "abcdef";
  checkStrContents(exp, s1+s2);
  EXPECT_EQ(std::string("abc"), std::string( s1.data_)) << "Data changed when added";
  EXPECT_EQ(std::string("def"), std::string( s2.data_)) << "Data changed when added"; 
}

TEST(StrTestOpPlus, AddSelf)
{
  Str s1("abc");
  std::string exp = "abcabc";
  checkStrContents(exp, s1+s1);
  EXPECT_EQ("abc", std::string(s1.data_)) << "Data changed when added to self";
}

TEST(StrTestOpPlus, AddCharArray)
{
	Str s1("abc");
	char s2[4] = "def";
	std::string exp = "abcdef";
	checkStrContents(exp, s1+s2);
	EXPECT_EQ(std::string("abc"), std::string(s1.data_)) << "Data changed when added to char array";
}
 
TEST(StrTestRelationalOps, Equals)
{
	Str s1("abc");
	Str s2("abc");
	Str s3("abcd");
	
	EXPECT_TRUE(s1 == s2) << "Expected True for Equals";
	EXPECT_FALSE(s1 == s3) << "Expected False for Equals";
}

TEST(StrTestRelationalOps, Neq)
{
	Str s1("abc");
	Str s2("abc");
	Str s3("abcd");
	
	EXPECT_FALSE(s1 != s2) << "Expected False for Not Equals";
	EXPECT_TRUE(s1 != s3) << "Expected True for Not Equals";
}

TEST(StrTestRelationalOps, LessThanGreaterThan)
{
	Str s1("a");
	Str s2("b");
	
	EXPECT_TRUE(s1 < s2) << "Expected True for Less than";
	EXPECT_TRUE(s2 > s1) << "Expected True for Greater than";
	EXPECT_FALSE(s2 < s1) << "Expected False for less than";
	EXPECT_FALSE(s1 > s2) << "Expected False for greater than";
}

TEST(StrTestPlusEq, PlusEqStr)
{
	Str s1("abc");
	Str s2("def");
	
	s1 += s2;
	std::string exp = "abcdef";
	checkStrContents(exp, s1);
	EXPECT_EQ(std::string(s2.data_), std::string("def")) << "Data changed in plus equals";
}

TEST(StrTestPlusEq, PlusEqCharArray)
{
	Str s1("abc");
	char s2[4] = "def";
	s1 += s2;
	
	std::string exp = "abcdef";
	checkStrContents(exp, s1);
	EXPECT_EQ(std::string(s2), std::string("def")) << "Data changed in plus equals";
}

TEST(StrTestPlusEq, PlusEqSelf)
{
	Str s1("abc");
	s1 += s1;
	std::string exp = "abcabc";
	checkStrContents(exp, s1);
}

TEST(StrTestSize, ConstructorSizes)
{
	Str s1("abcd");
	Str s2("a");
	Str s3(s2);
	Str s4;

	EXPECT_EQ(s1.size(), 4) << "Incorrect Size returned, expected 4, got " << s1.size();
	EXPECT_EQ(s3.size(), 1) << "Incorrect Size returned, expected 1, got " << s3.size();
	EXPECT_EQ(s2.size(), 1) << "Incorrect Size returned, expected 1, got " << s2.size();
	//EXPECT_EQ(s4.size(), 1);
}
TEST(StrTestSize, AdditionSizes)
{
	Str s1("abc");
	Str s2("def");
	
	Str s3 = s1 + s2;
	EXPECT_EQ(6, s3.size()) <<"Incorrect Size returned, expected 6, got " << s3.size();
	EXPECT_EQ(3, s1.size()) << "Incorrect Size returned, expected 3, got " << s1.size();
	EXPECT_EQ(3, s2.size()) << "Incorrect Size returned, expected 3, got " << s2.size();

	Str s4("abcd");
	Str s5("efgh");
	s4 += s5;
	EXPECT_EQ(8, s4.size()) << "Incorrect Size returned, expected 8, got " << s4.size();
	EXPECT_EQ(4, s5.size()) << "Incorrect Size returned, expected 4, got " << s5.size();
}
// Check if they're keeping track of size or just returning correctly in .size()
// Requires working += operator
/*
TEST(StrTestSize, SizeTracking)
{
	Str s1("ab");
	Str s2("cd");

	s1 += s2;
	int storedSize = s1.size_;
	int reportedSize = s1.size();
	int actualSize = 4;
	EXPECT_EQ(storedSize, reportedSize);
	EXPECT_EQ(storedSize, actualSize);
}
*/
TEST(StrTestIndexing, NormalIndex)
{
	Str s1("abcdefg");
	s1[0] = 'A';
	EXPECT_EQ(std::string("Abcdefg"), std::string(s1.data_));

	char const & c = s1[1];
	EXPECT_EQ(c, 'b') << "Incorrect Indexing";

	char const & c2 = s1[6];
	EXPECT_EQ(c2, 'g') << "Incorrect Indexing";
}

TEST(StrTestIndexing, IndexOutOfRange)
{
	Str s1("abc");
	try
	{
		s1[4];
		FAIL() << "Index Out of Bounds didn't throw exception";
	}
	catch(const std::exception& e)
	{
	}
}

TEST(StrTestIOStream, PrintTest)
{
	std::ofstream out;
	out.open ("TestWriteOp.o");
	Str s1("abcde");
	out << s1;
	out.close();

	std::ifstream in;
	in.open ("TestWriteOp.o");
	Str s2;
	in >> s2;
	EXPECT_EQ(std::string(s2.data_), std::string("abcde")) << "Got " << std::string(s2.data_) << " expected abcde";
	in.close();
}
