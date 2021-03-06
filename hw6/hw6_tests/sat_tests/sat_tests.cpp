#include <gtest/gtest.h>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <kwsys/SystemTools.hxx>
#include <user_code_runner.h>
#include <regex>
using namespace std;

vector<bool> parseFile(string file, int numVars)
{
	ifstream in(file);
	vector<bool> out(numVars);
	for(string line; getline(in, line);)
	{
		stringstream ss(line);
		int varNum, val;
		string temp;
		ss >> varNum;
		ss >> temp;
		ss >> val;
		if(numVars >= varNum && varNum > 0)
		{
			out[varNum - 1] = val;
		}
	}
	return out;
}

set<string> getStudentSet(string outputFile)
{
	ifstream in(outputFile);
	set<string> sentences_set;
	for(string line; getline(in, line);)
	{
		size_t first = line.find_first_not_of(" \t\n");
		size_t last = line.find_last_not_of(" \t\n");
		string sentence = line.substr(first, (last-first+1));
		sentences_set.insert(sentence);
	}
	return sentences_set;
}

testing::AssertionResult verifyAssignment(vector<bool> assignment, string inputFile)
{
	//Each line must evaluate to true
	ifstream in(inputFile);
	/*for(unsigned int i = 0; i < assignment.size(); i++)
	{
		cout << i << " " << assignment[i];
	}*/
	for(string line; getline(in, line);)
	{
		if(line[0] == 'p' || line[0] == 'c')
			continue;
		stringstream ss(line);
		int val;
		bool sat;
		while(ss >> val)
		{
			uint abs_val = abs(val);
			if (abs_val > assignment.size())
			{
				return testing::AssertionFailure() << "Invalid Variable encountered: " << val << endl;
			}
			if(val < 0)
			{
				sat = sat || !assignment[(-1*val)];
			}
			else
			{
				sat = sat || assignment[val];
			}
		}
		if(!sat)
		{
			return testing::AssertionFailure() << "A clause was not satisfied" << endl;
		}
	}
	return testing::AssertionSuccess();
}

testing::AssertionResult verifyStudentCode(string testName, string input, bool satValue, int numVars, bool useValgrind)
{
	string executablePath = SAT_EXECUTABLE;
	string testFolder =  TEST_BINARY_DIR "/sat_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	string inputFilePath = testFolder + "/input.txt";
	string outputFilePath = testFolder + "/output.txt";
	string stdoutFilePath = testFolder + "/stdout.txt";
	// write words to file
	ofstream inputWriter(inputFilePath);
	inputWriter << input << endl;
  
	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath, outputFilePath}, stdoutFilePath, useValgrind);
	testing::AssertionResult result = runner.execute();
	if(satValue)
	{
		vector<bool> studentAssignment;
		studentAssignment = parseFile(outputFilePath, numVars);
		/*for (unsigned int i = 0; i < studentAssignment.size(); i++)
		{
			cout << i << " " << studentAssignment[i] << endl;
		}*/
		return verifyAssignment(studentAssignment, inputFilePath);
	}
	else
	{
		ifstream in(outputFilePath);
		string line;
		getline(in, line);
		regex re(".*No solution.*", regex_constants::ECMAScript | regex_constants::icase); //Case Insensitive
		if(regex_match(line, re))
		{
			return testing::AssertionSuccess();
		}
		else
		{
			return testing::AssertionFailure() << "Expected No Solution, file did not contain no solution";
		}
	}
}
TEST(SAT, TrivialCNF)
{
	string input ="p cnf 1 1\n"
								"1 0";
	bool useValgrind = true;
	bool satValue = true;
	int numVars = 1;
	ASSERT_TRUE(verifyStudentCode("TrivialCNF", input, satValue, numVars, useValgrind));
}

TEST(SAT, TrivialCNFNeg)
{
	string input ="p cnf 1 1\n"
								"-1 0";
	bool useValgrind = true;
	bool satValue = true;
	int numVars = 1;
	ASSERT_TRUE(verifyStudentCode("TrivialCNFNeg", input, satValue, numVars, useValgrind));
}

TEST(SAT, TwoClauseSat)
{
	string input ="p cnf 1 2\n"
								"1 0\n"
								"1 0";
	bool useValgrind = true;
	bool satValue = true;
	int numVars = 1;
	ASSERT_TRUE(verifyStudentCode("TwoClauseSat", input, satValue, numVars, useValgrind));
}
TEST(SAT, TwoClauseUnSat)
{
	string input ="p cnf 1 2\n"
								"1 0\n"
								"-1 0";
	bool useValgrind = true;
	bool satValue = false;
	int numVars = 1;
	ASSERT_TRUE(verifyStudentCode("TwoClauseSat", input, satValue, numVars, useValgrind));
}
TEST(SAT, NominalSat)
{
	string input ="p cnf 4 3\n"
								"1 2 -4 3 0\n"
								"3 0\n"
								"-1 -2 0";
	bool useValgrind = true;
	bool satValue = true;
	int numVars = 4;
	ASSERT_TRUE(verifyStudentCode("NominalSat", input, satValue, numVars, useValgrind));
}
TEST(SAT, LargeCNFSat)
{
	string input;
	string fpath = TEST_BINARY_DIR "/sat_tests/largeSat.cnf";
	ifstream inputWriter(fpath);
	stringstream ss ;
	ss << inputWriter.rdbuf();
	input = ss.str();
	bool useValgrind = false;
	bool satValue = true;
	int numVars = 50;
	ASSERT_TRUE(verifyStudentCode("LargeSat", input, satValue, numVars, useValgrind));
}

TEST(SAT, LargeCNFUnSat)
{
	string input;
	string fpath = TEST_BINARY_DIR "/sat_tests/largeUnSat.cnf";
	ifstream inputWriter(fpath);
	stringstream ss ;
	ss << inputWriter.rdbuf();
	input = ss.str();
	bool useValgrind = false;
	bool satValue = false;
	int numVars = 100;
	ASSERT_TRUE(verifyStudentCode("LargeUnSat", input, satValue, numVars, useValgrind));
}
TEST(SAT, NominalUnsat)
{
	string input=
	"p cnf 2 3\n"
	"1 0\n"
	"-1 0\n"
	"2 -2 0";
	bool useValgrind = true;
	bool satValue = false;
	int numVars = 2;
	ASSERT_TRUE(verifyStudentCode("NominalUnsat", input, satValue, numVars, useValgrind));
}

TEST(SAT, NominalUnsat2)
{
	string input=
	"p cnf 4 8\n"
	"-1 2 4 0\n"
	"-2 3 4 0\n"
	"1 -3 4 0\n"
	"1 -2 -4 0\n"
	"2 -3 -4 0\n"
	"-1 3 -4 0\n"
	"1 2 3 0\n"
	"-1 -2 -3 0\n";
	bool useValgrind = true;
	bool satValue = false;
	int numVars = 4;
	ASSERT_TRUE(verifyStudentCode("NominalUnsat2", input, satValue, numVars, useValgrind));
}

TEST(SAT, ExtraVars)
{
	string input = //only variables 1 and 2 need to be assigned
	"p cnf 4 3\n"
	"-1 3 0\n"
	"-1 4 0\n"
	"-2 0";
	bool useValgrind = true;
	bool satValue = true;
	int numVars = 4;
	ASSERT_TRUE(verifyStudentCode("ExtraVars", input, satValue, numVars, useValgrind));
}


