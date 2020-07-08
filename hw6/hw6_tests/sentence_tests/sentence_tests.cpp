#include <gtest/gtest.h>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <kwsys/SystemTools.hxx>
#include <user_code_runner.h>
using namespace std;

set<string> iterativeSolution(vector<vector<string>> input_vec)
{
	vector<string> adjectives = input_vec[0];
	vector<string> nouns = input_vec[1];
	vector<string> verbs = input_vec[2];
	vector<string> adverbs = input_vec[3];
	set<string> sentences;
	for(unsigned int i = 0; i <= adjectives.size(); i++)
	{
		for(unsigned int j = 0; j < nouns.size(); j++)
		{
			for(unsigned int k = 0; k < verbs.size(); k++)
			{
				for(unsigned int l = 0; l <= adverbs.size(); l++)
				{
					string noun, adjective, verb, adverb;
					if (i >= adjectives.size())
						adjective = "";
					else
						adjective = adjectives[i] + " ";
					if (j >= nouns.size())
						noun = "";
					else
						noun = nouns[j];
					if (k >= verbs.size())
						verb = "";
					else
						verb = verbs[k];
					if (l >= adverbs.size())
						adverb = "";
					else{
						adverb = " " + adverbs[l];}
					string sentence = "The " + adjective  + noun + " " + verb + adverb + ".";
					sentences.insert(sentence);
				}
			}
		}
	}
	sentences.insert(to_string(sentences.size()) + " sentences.");
	return sentences;
}

vector<vector<string>> parseFile(string file)
{
	ifstream in(file);
	vector<vector<string>> out;
	for(string line; getline(in, line);)
	{
		vector<string> words;
		stringstream ss(line);
		string word;
		while(ss >> word)
		{
			words.push_back(word);
		}
		out.push_back(words);
	}
	return out;
}

testing::AssertionResult compareSets(set<string> correct, set<string> user)
{
	if(correct.size() != user.size())
	{	
		return testing::AssertionFailure() << "incorrect number of sentences, expected " << correct.size() << " got " << user.size() << endl;
	}
	for(auto it = correct.begin(); it != correct.end(); ++it)
	{
		auto loc = user.find(*it);
		if(loc != user.end())
		{
			user.erase(loc);
		}
		else
		{
			return testing::AssertionFailure() << "user did not include " << *it << endl;
		}
	}
	return testing::AssertionSuccess();
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

testing::AssertionResult verifyStudentCode(string testName, string input, bool useValgrind)
{
	string executablePath = SENTENCES_EXECUTABLE;
	string testFolder =  TEST_BINARY_DIR "/sentence_tests/testFiles/" + testName;
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

	vector<vector<string>> in_vec;
	in_vec = parseFile(inputFilePath);
	set<string> correct_set = iterativeSolution(in_vec);
	set<string>	user_set = getStudentSet(outputFilePath);
	cout << correct_set.size() << " " << user_set.size() << endl;
	return compareSets(correct_set, user_set);
}

TEST(sentences, Nominal1)
{
	string input ="big\n"
								"boy girl\n"
								"swam ran\n"
								"quickly";
	bool useValgrind = true;
	ASSERT_TRUE(verifyStudentCode("Nominal1", input, useValgrind));
}

TEST(sentences, Nominal2)
{
	string input =
	"red blue\n"
	"cat dog\n"
	"jumped fell\n"
	"swiftly suddenly";
	bool useValgrind = true;
	ASSERT_TRUE(verifyStudentCode("Nominal2", input, useValgrind));
}

TEST(sentences, Nominal3)
{
	string input =
 	"a b c d\n"
	"e f g h\n"
	"i j k l\n"
	"m n o p";
	bool useValgrind = true;
	ASSERT_TRUE(verifyStudentCode("Nominal3", input, useValgrind));
}

TEST(sentences, MissingAdjectives)
{
	string input =
 	"\n"
	"e f\n"
	"i j\n"
	"a, b";
	bool useValgrind = true;
	ASSERT_TRUE(verifyStudentCode("MissingAdjectives", input, useValgrind));
}

TEST(sentences, MissingAdverbs)
{
	string input =
	"a b\n"
	"c d\n"
	"e f\n"
	"";
	bool useValgrind = true;
	ASSERT_TRUE(verifyStudentCode("MissingAdverbs", input, useValgrind));	
}
