#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <cstdlib>
#include "avlbst.h"

void readFile(char *filename, std::vector<std::vector<int> *> &clauses, AVLTree<int, int> &variables)
{
    std::ifstream iFile(filename);
    std::string line;
    std::string word;
    getline(iFile, line);
    std::stringstream ss(line);
    ss >> word;
    while (word == "c")
    { //To get through all the c's
        getline(iFile, line);
        ss.str(line);
        ss.clear();
        ss >> word;
    }
    ss >> word; //=cnf
    ss >> word; //=number of variables
    int numVars = std::stoi(word);
    for (int i = 1; i < numVars + 1; i++)
    {
        variables.insert(std::make_pair(i, 0));
    }

    ss >> word;
    int numClauses = std::stoi(word);
    for (int i = 0; i < numClauses; i++)
    {
        getline(iFile, line);
        std::vector<int> *clause = new std::vector<int>();
        ss.str(line);
        ss.clear();
        while (ss >> word && word != "0")
        {
            clause->push_back(std::stoi(word));
        }
        if(clause->size()>0){ // if file states there are 5 clauses but there's nothing in them, we don't care
            clauses.push_back(clause);
        }
    }
}

bool isValid(std::vector<std::vector<int> *> &clauses, AVLTree<int, int> &variables, bool baseCase)
{

    //returns true if there's 1+ true boolean or undetermined for every clause
    for (size_t i = 0; i < clauses.size(); i++)
    {
        bool validForClause = false;
        for (size_t j = 0; j < clauses[i]->size(); j++)
        {
            int var = (*clauses[i])[j];
            if (baseCase && variables.find(std::abs(var))->second * var > 0)
            {
                validForClause = true;
                break;
            }
            else if (!baseCase && variables.find(std::abs(var))->second * var >= 0)
            {
                validForClause = true;
                break;
            }
        }
        if (!validForClause)
        {
            return false;
        }
    }
    return true;
}


//Pls don't take points off for my awesome yet accurate function name
//Removes any extraneous bools from solution
void trimTheFat(std::vector<std::vector<int> *> &clauses, AVLTree<int, int> &variables)
{
    for (size_t i = 1; i < variables.size() + 1; i++)
    {
        int value = variables.find(i)->second;
        variables.find(i)->second = 0;
        if (!isValid(clauses, variables, true))
        {
            variables.find(i)->second = value;
        }
    }
}

//returns true if variables are set in such a way that all clauses=true and false if it has failed and needs to backtrack.
//If first call returns false, no possible answer
bool boolSatisfyHelper(int boolToEdit, int value, std::vector<std::vector<int> *> &clauses, AVLTree<int, int> &variables)
{
    if (isValid(clauses, variables, true))
    {
        return true;
    }
    else
    {
        variables.find(boolToEdit)->second = value;
        if (isValid(clauses, variables, false))
        {
            if (boolSatisfyHelper(boolToEdit + 1, 1, clauses, variables))
            {
                return true;
            }
            else if (boolSatisfyHelper(boolToEdit + 1, -1, clauses, variables))
            {
                return true;
            }
        }
        //Backtrack
        variables.find(boolToEdit)->second = 0;
        return false;
    }
}
//Wrapper for clean interface
bool boolSatisfy(std::vector<std::vector<int> *> &clauses, AVLTree<int, int> &variables){
    return boolSatisfyHelper(1,1,clauses,variables) || boolSatisfyHelper(1,-1,clauses,variables);
}


int main(int argc, char *argv[])
{
    AVLTree<int, int> variables; //-1=false,0=unassigned,1=true
    std::vector<std::vector<int> *> clauses;
    readFile(argv[1], clauses, variables); // try catch?
    std::ofstream oFile(argv[2]);          //nonexistent file errors?
    if (boolSatisfy(clauses, variables))
    {
        trimTheFat(clauses, variables);
        for (size_t i = 1; i < variables.size() + 1; i++)
        {
            int val = variables.find(i)->second;
            if (val != 0)
            {
                oFile << i << " = " << (val + 1) / 2 << std::endl; //converts a -1 to a 0
            }
        }
    }
    else if(clauses.size()>0 && variables.size()>0)
    {
        oFile << "No solution";
    }

    for (size_t i = 0; i < clauses.size(); i++)
    {
        delete clauses[i];
    }

    return 0;
}