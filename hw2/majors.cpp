#include <map>
#include <iostream>
#include <set>
#include <fstream> 
#include <string>
#include <sstream>
#include "setops.h"
#include "setops.cpp"

using namespace std;

struct Student
{
    string name;
    set<string> majors;
};

void setStudent(string line, Student* stu){
    string name="";
    bool atMajors=false;
    string word;
    stringstream ss(line);
    while(ss>>word){
        if(atMajors==false){
            if(word.back() != ','){
                name+=word;
                name+=" ";
            }
            else{
                word = word.substr(0,word.length()-1);
                name+=word;
                atMajors=true;
            }
        }
        else{
            stu->majors.insert(word);
        }
    }
    stu->name = name;
}

void readFile(string fileName, string* wholeFile){
	ifstream iFile(fileName);
    *wholeFile = "";
    getline(iFile, *wholeFile, '\0');
    iFile.close();
}


void setKeys(map<string, set<string>> majorMap, string filename){
    string line;
    ifstream iFile(filename);
    getline(iFile,line);
    while(line!="\0"){
        set<string> empty;
        majorMap.insert(pair<string,set<string>>(line,empty));
        getline(iFile,line);
    }    
}

void storeMajorData(string wholeFile, string filename, map<string,set<string>> majorMap){
    string line="filler";
    ifstream iFile(filename);
    while(line!="\0"){
        getline(iFile,line);
        Student student;
        setStudent(line,&student);
        set<string> majors;
        for (map<string,set<string>>::iterator it=majorMap.begin(); it!=majorMap.end(); ++it) {
            majors.insert(it->first);        
        }
        set<string> intersection = student.majors & majors;

        for(set<string>::iterator it=intersection.begin(); it!=intersection.end();++it){
            
            set<string> currentSet = majorMap.find(*it)->second;
            currentSet.insert(student.name);
            majorMap.insert(pair<string, set<string>>(*it, currentSet));
        }
    }
}

void printMajors(map<string,set<string>> majorMap){
    for (map<string,set<string>>::iterator it=majorMap.begin(); it!=majorMap.end(); ++it) {       
    }    
}

int main (int argc, char * argv[]){
    map<string, set<string>> majorMap;

    setKeys(majorMap, argv[2]);
    string wholeStudentFile;
    readFile(argv[1], &wholeStudentFile);
    storeMajorData(wholeStudentFile, argv[1],majorMap);
    printMajors(majorMap);

    return 0;
}
