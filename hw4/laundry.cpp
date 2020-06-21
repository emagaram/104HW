#include "stack.h"
#include <iostream>
#include <sstream>
#include <fstream>
std::string readFile(std::string fileName)
{
    //Got from earlier project
    std::ifstream iFile(fileName);
    std::string output = "";
    std::getline(iFile, output, '\0');
    iFile.close();
    return output;
}

int main(int argc, char *argv[])
{
    Stack<int> s;
    std::string fileNameIn = argv[1];
    std::string fileNameOut = argv[2];
    std::string fileLine = readFile(fileNameIn);
    std::ofstream ofile(fileNameOut);
    std::string word;
    std::stringstream ss(fileLine);

    //Takes every word in from file and handles it accordingly
    while (ss >> word)
    {
        int num = std::stoi(word);

        //A towel
        if (num <= 0)
        {
            s.push(num);
        }
        else //num of towels to pickup
        {
            if (size_t(num) > s.size())
            {
                //Shrink num so that it doesn't
                //go beyond
                num = s.size();
            }
            //Will run a maximum of n times
            //throughout the entire while loop so still O(N)
            for (int i = 0; i < num; i++)
            {
                if (s.top() == -1)
                {
                    ofile << "white ";
                }
                else
                {
                    ofile << "black ";
                }

                s.pop();
            }
            ofile << std::endl;
        }
    }
    ofile.close();
}
