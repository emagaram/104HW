#include "stack.h"
#include <iostream>
#include <sstream>
std::string readFile()
{
    return "0  0  0  -1  20  -1  2";
    //"0  0  0  -1  2  -1  2";
}
void print(std::string message)
{
}
int main()
{
    Stack<int> *s = new Stack<int>();
    std::string fileLine = readFile();
    std::string word;
    std::stringstream ss(fileLine);
    while (ss >> word)
    {
        int num = std::stoi(word);
        if (num <= 0)
        {
            s->push(num);
        }
        else
        {
            if (num > s->size())
            {
                num = s->size();
            }

            //Will run a maximum of n times
            for (int i = 0; i < num; i++)
            {
                if (s->top() == -1)
                {
                    std::cout << "white ";
                }
                else
                {
                    std::cout << "black ";
                }

                s->pop();
            }
            std::cout << std::endl;
        }
    }
}
