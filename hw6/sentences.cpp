#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char *filename, std::vector<std::vector<std::string> > &words);

// client interface
void generateSentences(std::vector<std::vector<std::string> > &words, ofstream &ofile);

// recursive helper function
void genHelper(vector<vector<string> > &words,
               ofstream &ofile,
               int currentOption,
               string sentence,
               int &numSentences);

void readWords(char *filename, std::vector<std::vector<std::string> > &words)
{
  std::ifstream iFile(filename);
  std::string line;
  std::string word;
  for (int i = 0; i < 4; i++)
  {
    getline(iFile, line);
    std::stringstream ss(line);
    std::vector<std::string> vec;
    if (i == 0 || i == 3)
    {
      std::string emptyStr = "";
      vec.push_back(emptyStr); //emptystr is inserted since these are optional words
    }
    while (ss >> word)
    {
      vec.push_back(word);
    }
    words.push_back(vec); //index 0 is adj, 1 is sub, 2 is verb, 3 is adv,
  }
}

void generateSentences(vector<vector<string> > &words, ofstream &ofile)
{
  int numSentences = 0;
  genHelper(words, ofile, 0, "The", numSentences);
  ofile << numSentences << " sentences.";
}

void genHelper(vector<vector<string> > &words,
               ofstream &ofile,
               int currentOption,
               string sentence,
               int &numSentences)
{
  if (currentOption == 4)
  {
    ofile << sentence << "." << std::endl;
    numSentences++;
  }
  else
  {

    for (size_t i = 0; i < words[currentOption].size(); i++)
    {
      std::string temp;
      if (words[currentOption][i] != "")
      {
        temp = sentence + " " + words[currentOption][i];
      }
      else
      {
        temp = sentence + words[currentOption][i];
      }
      genHelper(words, ofile, currentOption + 1, temp, numSentences);
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if (words.size() < 4)
  {
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);

  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
