#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
#include <array>
using namespace std;

int main(int argc, char *argsv[])
{
	int num_tweets = atoi(argsv[1]);
	int num_hashtags_per_tweet = atoi(argsv[2]);
	cout << "HERE" <<endl;
	vector<string> users;
	users.push_back("a");
	users.push_back("b");
	stringstream filename;
	filename << "runtime_test_files/";
	filename << num_tweets << "_" << num_hashtags_per_tweet << ".dat";
	ofstream out(filename.str());
	cout << users.size() <<endl;
	out << users.size() << endl;
	cout << "loop" << endl;
	for(unsigned int i = 0; i < users.size(); i++)
	{
		out << users[i] << endl;
	}
	cout << "HERE";
	for(int i = 0; i < num_tweets; i++)
	{
		out  << "2019-11-11 11:11:11 " << users[rand() % users.size()] << " ";
		for(int j = 0; j < num_hashtags_per_tweet; j++)
		{
			char tag = 'a' + rand() % 26; //generate random tag which is just a letter
			out << "#" << tag << " ";
		}		
		out << endl;
	}
	out.close();
	return 0;
}
