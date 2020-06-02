#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>
using namespace std;
int main (int argc, char * argv[]){
	vector<string> uniqueUsers;
	vector<string> hashtags;
	string wholeFile="";
	string piece="";
	string line;
	string stringCounter;
	int tweetCount = 0;
	ifstream iFile(argv[1]);
	if(iFile.fail()){
		cout << "Error!\n";
		return 0;
	}
	getline(iFile, wholeFile, '\0');
	iFile.close();
	
	//To get tweetCount
	
	ifstream iFile2(argv[1]);
	while(piece!=wholeFile){
		getline(iFile2, line);
		if(line!=""){
			tweetCount++;
		}
		line+="\n";
		piece+=line;
	}

  	string word;
  	stringstream ss(wholeFile);
  	while(ss >> word){
  		if(word.substr(0,1) == "@"){
  			word = word.substr(1,word.length());
  			bool exists = false;
  			for(int i = 0; i < uniqueUsers.size();i++){
  				if(uniqueUsers[i]==word){
  					exists = true;
  				}
  			}
  			if(!exists){
  				uniqueUsers.push_back(word);	
  			}	
  		}
  		else if(word.substr(0,1) == "#"){
  			word = word.substr(1,word.length());
  			bool exists = false;
  			for(int i = 0; i < hashtags.size();i++){
  				if(hashtags[i]==word){
  					exists = true;
  				}
  			}
  			if(!exists){
  				hashtags.push_back(word);	
  			}	
  		}	
  	}
  	cout << "1. Number of tweets=" << tweetCount << endl;
  	cout << "2. Unique users" << endl;
  	for(int i = 0; i < uniqueUsers.size(); i++){
  		cout << uniqueUsers[i] << endl;
  	}
  	cout << "3. Unique hashtags" << endl;
  	for (int i = 0; i < hashtags.size(); i++)
  	{
  		cout << hashtags[i] << endl;
  	}
}
