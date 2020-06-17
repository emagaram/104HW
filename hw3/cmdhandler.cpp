#include "cmdhandler.h"
#include "util.h"
#include <sstream>
using namespace std;

QuitHandler::QuitHandler()
{
}

QuitHandler::QuitHandler(Handler *next)
	: Handler(next)
{
}

bool QuitHandler::canHandle(const std::string &cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::cout <<"Reading QUIT!!!!!!!!!!!!!!!!!!!";
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{
}
AndHandler::AndHandler(Handler *next) : Handler (next)
{
}

bool AndHandler::canHandle(const std::string &cmd) const
{
	return cmd == "AND";
	
}
Handler::HANDLER_STATUS_T AndHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::string word;
	std::string line;
	std::vector<string> *terms;
	std::vector<Tweet*> output;
	std::getline(instr, line);

	std::stringstream ss(line);

	
	 while (ss>>word)
	 {
		 std::cout<<"RAN";
	 	//terms->insert(word);
	 }
	std::cout<<terms->size();
	output = eng->search(*terms, 0);
	
	if(output.size()==0){
		std::cout<<"No matches.";
	}
	return HANDLER_OK;
}

OrHandler::OrHandler()
{
}
OrHandler::OrHandler(Handler *next)
{
}

bool OrHandler::canHandle(const std::string &cmd) const
{
	return cmd == "OR";
}
Handler::HANDLER_STATUS_T OrHandler::process(TwitEng *eng, std::istream &instr) const
{
	std::cout << "HOOOO";
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{
}
TweetHandler::TweetHandler(Handler *next)
{
}

bool TweetHandler::canHandle(const std::string &cmd) const
{
	return cmd == "TWEET";
}
Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng *eng, std::istream &instr) const
{
	return HANDLER_OK;
}