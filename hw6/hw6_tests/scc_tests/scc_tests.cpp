#include <gtest/gtest.h>
#include <string>
#include <user_code_runner.h>
#include <kwsys/SystemTools.hxx>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <set>
#include <map>

using namespace std;

void printComponents(set<set<string>> components)
{
	for(auto c : components)
	{
		for(auto name : c)
		{
			cout << name << " ";
		}
		cout << endl;
	}
}
string getStudentOutput(string testName, string input, bool useValgrind)
{
	string executablePath = SCC_EXECUTABLE;
	string testFolder = TEST_BINARY_DIR "/scc_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	string databaseFilePath = testFolder + "/database.txt";
	string inputCommandFilePath = testFolder + "/command.txt";
	string outputFilePath = testFolder +"/output.txt";
	string stdoutFilePath = testFolder + "/stdout.txt";

	//write input to file
	ofstream inputWriter(databaseFilePath);
	inputWriter << input << endl;

	UserCodeRunner runner(testFolder, executablePath, {databaseFilePath}, stdoutFilePath, useValgrind);
	runner.setStdin("SCC " + outputFilePath + "\nQUIT", inputCommandFilePath);
	runner.execute();
	
	return outputFilePath;
}

map<string, vector<string>> makeGraph(string input)
{
	stringstream ss(input);
	int numUsers;
	ss >> numUsers;
	string line;
	map<string, vector<string>> graph;
	while(getline(ss, line))
	{
		if(line.find_first_not_of(" \t\n") == string::npos)
		{
			continue; //skip empty lines
		}
		vector<string> neighbors;
		stringstream lineStream(line);
		string node;
		lineStream >> node;
		string neighbor;
		while(lineStream >> neighbor)
		{
			neighbors.push_back(neighbor);
		}
		graph.insert(pair<string, vector<string>>(node, neighbors));
	}
	return graph;
}

//Taken from Wikipedia
set<string> strongConnect(string name, map<string, vector<string>> graph, stack<string>& s, set<string>& onStack, map<string, int>& lowlink, int& index, map<string, int>& indices, set<set<string>>& allComponents)
{
	set<string> component;
	indices[name] = index;
	lowlink[name] = index;
	index ++;
	s.push(name);
	onStack.insert(name);
	for(auto w : graph[name])
	{
		if(indices.find(w) == indices.end())
		{
			allComponents.insert(strongConnect(w, graph, s, onStack, lowlink, index, indices, allComponents));
			lowlink[name] = min(lowlink[name], lowlink[w]);
		}
		else if(onStack.find(w) != onStack.end())
		{
			lowlink[name] = min(lowlink[name], indices[w]);
		}
	}
	
	if(lowlink[name] == indices[name])
	{
		string w;
		do
		{
			w = s.top();
			s.pop();
			onStack.erase(w);
			component.insert(w);
		} while( w!= name);
	}
	
	return component;
}
set<set<string>> computeComponents(string input)
{
	map<string, vector<string>> graph = makeGraph(input);
	set<set<string>> allComponents;
	int index = 0;
	stack<string> s;
	set<string> onStack;
	map<string, int> lowlink;
	map<string, int> indices;
	for (auto keyValue : graph)
	{
		string name = keyValue.first;
		vector<string> neighbors = keyValue.second;
		if(indices.find(name) == indices.end())
		{
			allComponents.insert(strongConnect(name, graph, s, onStack, lowlink, index, indices, allComponents));
		}
	}

	//strip empty components
	for(auto c : allComponents)
	{
		if(c.size() == 0)
		{
			allComponents.erase(c);
		}
	}
	return allComponents;
}



set<set<string>> parseStudentOutputs(string outputFilePath)
{
	ifstream in(outputFilePath);
	string line;
	set<set<string>> components;
	while(getline(in, line))
	{
		if(line.find("component") != string::npos || line.find("Component") != string::npos )
		{
			set<string> currComponent;
			while(true)
			{
				if(!getline(in, line))
				{
					components.insert(currComponent);
					return components;
				}
				if(line.find_first_not_of(" \n\t") != string::npos)
				{
					//cout << line << endl;
					string node;
					stringstream ss(line);
					ss >> node;
					if (currComponent.find(node) != currComponent.end())
						throw "Duplicate Node in Component";//TODO Catch
					currComponent.insert(node);
				}
				else
				{
					break;
				}
			}
			components.insert(currComponent);
		}
	}
	return components;
}

testing::AssertionResult verifyComponents(set<set<string>> c1, set<set<string>> c2)
{
	//Find component in c2 that matches each component in c1
	if(c1.size() != c2.size())
	{	
		return testing::AssertionFailure() << "expected #components " << c1.size()<< ", but got " << c2.size();
	}
	for(auto component : c1)
	{
		auto firstName = component.begin();
		set<string> correspondingComponent;
		for(auto studentComponent : c2)
		{
			if(studentComponent.find(*firstName) != studentComponent.end())
			{
				correspondingComponent = studentComponent;
				break;
			}
		}
		if (correspondingComponent.size() == 0)
		{
			return testing::AssertionFailure() << "Reached an empty component";
		}
		//We have the student component and the correct component, compare item by item
		if(correspondingComponent.size() != component.size())
		{
			return testing::AssertionFailure() << "Components with " << *firstName << " are two different sizes, expected " << component.size() << " got " << correspondingComponent.size(); 
		}
		for(string correctName : component)
		{
			if(correspondingComponent.find(correctName) == correspondingComponent.end())
				return testing::AssertionFailure() << "Could not find " << correctName << " in component";
		}
	}
	return testing::AssertionSuccess();
}

testing::AssertionResult checkCode(string testName, string input)
{
	string outputFile = getStudentOutput(testName, input, true);
	set<set<string>> studentComponents = parseStudentOutputs(outputFile);
	set<set<string>> correctComponents = computeComponents(input);
	return verifyComponents(correctComponents, studentComponents);
}

TEST(SCC, 3Nodes1)
{
	string input =
	"3\n"
	"Mark Eric Sean\n"
	"Eric Sean\n"
	"Sean Eric\n";

	ASSERT_TRUE(checkCode("3Nodes1", input));
}

TEST(SCC, 3Nodes2)
{
	string input =
	"3\n"
	"Mark Eric Sean\n"
	"Eric Sean Mark\n"
	"Sean \n";
	ASSERT_TRUE(checkCode("3Nodes2", input));
}

TEST(SCC, 3Nodes3)
{
	string input =
	"3\n"
	"Mark Eric Sean\n"
	"Eric Sean Mark\n"
	"Sean Eric\n";
	ASSERT_TRUE(checkCode("3Nodes3", input));
}

TEST(SCC, Cycle)
{
	string input =
	"3\n"
	"Mark Eric\n"
	"Eric Sean\n"
	"Sean Mark\n";
	ASSERT_TRUE(checkCode("Cycle", input));
}

TEST(SCC, NoEdges)
{
	string input =
	"3\n"
	"Mark\n"
	"Eric\n"
	"Sean\n";
	ASSERT_TRUE(checkCode("NoEdges", input));
}

TEST(SCC, TrivialSCCOnly)
{
	string input = 
	"3\n"
	"Mark Eric\n"
	"Eric Sean\n"
	"Sean\n";
	ASSERT_TRUE(checkCode("TrivialSCCOnly", input));
}

TEST(SCC, 3NeighborsRandomGraph10)
{
	srand(42);
	int n = 10;
	int numNeighbors = 3;
	string input = to_string(n) + "\n";
	for(int i = 0; i < n; i++)
	{
		input += to_string(i) + " ";
		for(int j = 0; j < numNeighbors; j++)
		{
			input += to_string(rand() % n) + " ";
		}
		input += "\n";
	}
	ASSERT_TRUE(checkCode("3RandomGraph10", input));
}

TEST(SCC, 2NeighborsRandomGraph10)
{
	srand(42);
	int n = 10;
	int numNeighbors = 2;
	string input = to_string(n) + "\n";
	for(int i = 0; i < n; i++)
	{
		input += to_string(i) + " ";
		for(int j = 0; j < numNeighbors; j++)
		{
			input += to_string(rand() % n) + " ";
		}
		input += "\n";
	}
	ASSERT_TRUE(checkCode("2RandomGraph10", input));
}

TEST(SCC, 1NeighborsRandomGraph10)
{
	srand(42);
	int n = 10;
	int numNeighbors = 1;
	string input = to_string(n) + "\n";
	for(int i = 0; i < n; i++)
	{
		input += to_string(i) + " ";
		for(int j = 0; j < numNeighbors; j++)
		{
			input += to_string(rand() % n) + " ";
		}
		input += "\n";
	}
	ASSERT_TRUE(checkCode("1RandomGraph10", input));
}

TEST(SCC, 5NeighborsRandomGraph100)
{
	srand(42);
	int n = 100;
	int numNeighbors = 5;
	string input = to_string(n) + "\n";
	for(int i = 0; i < n; i++)
	{
		input += to_string(i) + " ";
		for(int j = 0; j < numNeighbors; j++)
		{
			input += to_string(rand() % n) + " ";
		}
		input += "\n";
	}
	ASSERT_TRUE(checkCode("5RandomGraph100", input));
}

TEST(SCC, 25NeighborsRandomGraph100)
{
	srand(42);
	int n = 100;
	int numNeighbors = 25;
	string input = to_string(n) + "\n";
	for(int i = 0; i < n; i++)
	{
		input += to_string(i) + " ";
		for(int j = 0; j < numNeighbors; j++)
		{
			input += to_string(rand() % n) + " ";
		}
		input += "\n";
	}
	ASSERT_TRUE(checkCode("25RandomGraph100", input));
}
