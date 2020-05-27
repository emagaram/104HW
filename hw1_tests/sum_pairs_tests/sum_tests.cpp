//
// CS104 HW1 wordsearch test suits
//

#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>


// regular expressions for reading output
//kwsys::RegularExpression wordMatchRegex(
//		R"(([a-z]+) starts at \(row,col\) = \(([0-9]+),([0-9]+)\) and proceeds ([a-z]+))");
//kwsys::RegularExpression doesNotOccurRegex("[a-z]+ does NOT occur");

// Tries running the user's wordsearch program on the given input, and reports whether it produced the expected output
testing::AssertionResult checkSums(std::string const & testName, std::string const & inputContents, bool correctlyFormatted, bool useValgrind = true)
{
	std::string executablePath = SUM_PAIRS_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/sum_pairs_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";
	std::string stdoutFilePath = testFolder + "/stdout.txt";
	
	// write numbers to file
	std::ofstream inputWriter(inputFilePath);
	inputWriter << inputContents << std::endl;

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath, outputFilePath}, stdoutFilePath, useValgrind);
	testing::AssertionResult result = runner.execute();



	// read output
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}
		
		int val;
		std::vector<int> actualSums;
		while( outputFile >> val ){
		  actualSums.push_back(val);
		}
		if(!correctlyFormatted){
		  // check for 0
		  if(0U == actualSums.size() ){
		    return testing::AssertionFailure() << "Invalid input format...Expected a 0 to be output but no output was found";
		  }
		  else if(0 != actualSums.front()){
		    return testing::AssertionFailure() << "Invalid input format...Expected a 0 to be output but no output was found";
		  }
		}
		else {
		  // compute the correct values and check them
		  std::vector<int> inputVals;
			std::vector<int> expectedSums;
		  std::stringstream ss(inputContents);
		  ss >> val; // get the number of values
		  while( ss >> val ){
		    inputVals.push_back(val);
		  }
		  unsigned origSize = inputVals.size();
		  for(unsigned i = 0; i < (origSize+1)/2; i++){
		    expectedSums.push_back(inputVals[origSize - i - 1] + inputVals[i]);
		  }
			if(expectedSums.size() != actualSums.size() ){
		    return testing::AssertionFailure() << "Incorrect number of sums in output file";
		  }
		  else {
		    for(unsigned i = 0; i < expectedSums.size(); i++){
		      if(expectedSums[i] != actualSums[i]) {
			return testing::AssertionFailure() << "Mismatch at entry " << i << " Expected: " << expectedSums[i] << " / Actual: " << actualSums[i];
		      }
		    }
		  }
		}

	}
	return testing::AssertionSuccess();
};


TEST(sum_pairs, BadInput1)
{
  ASSERT_TRUE(checkSums("BadInput1",
			"abc 1 2 3 4", false, true));
}
const std::string mediumSize =
"9\n"
"1000\n"
"3000\n"
"5000\n"
"7000\n"
"9000\n"
"8000\n"
"6000\n"
"4000\n"
"2000\n";
											   
TEST(sum_pairs, NominalInput1)
{
  ASSERT_TRUE(checkSums("NominalInput1",
			mediumSize, true, true));
}

const std::string smallSize =
"4\n"
"1000\n"
"3000\n"
"5000\n"
"7000\n";

TEST(sum_pairs, NominalInput2)
{
	ASSERT_TRUE(checkSums("NominalInput2",
				smallSize, true, true));
}
TEST(sum_pairs, NominalInput3)
{
	srand(42);
	int numInts = 1000;
	std::string largeSize = std::to_string(numInts) + "\n";
	for (int i = 0; i < numInts; i++)
	{
		largeSize += std::to_string(rand() % 100) + "\n";
	}
	ASSERT_TRUE(checkSums("NominalInput3",
				largeSize, true, true));
}	
const std::string evenSum =
"2\n"
"5\n"
"10\n";											   

TEST(sum_pairs, EvenSum1)
{
	ASSERT_TRUE(checkSums("evenSum1", evenSum, true, true));
}

const std::string single =
"1\n"
"5\n";

TEST(sum_pairs, SingleSum)
{
	ASSERT_TRUE(checkSums("singleSum", single, true, true));
}
const std::string zero = 
"0\n";

TEST(sum_pairs, ZeroInput)
{
	ASSERT_TRUE(checkSums("ZeroInput", zero, true, true));
}
