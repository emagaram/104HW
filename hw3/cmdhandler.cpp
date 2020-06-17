#include "cmdhandler.h"
#include "util.h"
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
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{
}
AndHandler::AndHandler(Handler *next)
{
}

bool AndHandler::canHandle(const std::string &cmd) const
{
}
Handler::HANDLER_STATUS_T AndHandler::process(TwitEng *eng, std::istream &instr) const
{
}

OrHandler::OrHandler()
{
}
OrHandler::OrHandler(Handler *next)
{
}

bool OrHandler::canHandle(const std::string &cmd) const
{
}
Handler::HANDLER_STATUS_T OrHandler::process(TwitEng *eng, std::istream &instr) const
{
}

TweetHandler::TweetHandler()
{
}
TweetHandler::TweetHandler(Handler *next)
{
}

bool TweetHandler::canHandle(const std::string &cmd) const
{
}
Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng *eng, std::istream &instr) const
{
}