#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

void readFile(char *filename, std::vector<std::vector<std::string>> &words)
{
    std::ifstream iFile(filename);
    std::string line;
    std::string word;
    getline(iFile, line);
}

int main(int argc, char *argv[])
{
    std::map<int, int> variables; //-1=false,0=unassigned,1=true
    return 0;
}