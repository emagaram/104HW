#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class Course {
public:
  Course(std::string name, int the_type);
  ~Course();
  // Public method useful for all types of Courses
  void setGrades(const std::map<std::string, double>& new_grades);

  void setScale(const std::map<std::string, double>& the_scale);

  void setPassThreshold(double thresh);

  // All courses must be able to output the students and their grades
  // by calling a member function with this signature
  void outputGrades();
private:
  std::string courseName;
  int type; // 1 = Pass/NoPass, 2 = straight scale, 3=Custom scale
  std::map<std::string, double> grades;  // map student names to numeric total
  std::map<std::string, double> scale;   // map letter grade to lower bound
  double threshold;  // lower bound for Pass
};

Course::Course(std::string name, int the_type)
{
  courseName = name;
  type = the_type;
  if(type == 2 || type == 3){
    // Scale to be used for type 2 (Straight scale) courses and
    // Default scale for type 3 = Custom scale that can
    // be replaced by a call to setScale()
    scale.insert(std::make_pair("A", 90));
    scale.insert(std::make_pair("B", 80));
    scale.insert(std::make_pair("C", 70));
    scale.insert(std::make_pair("D", 60));
    scale.insert(std::make_pair("F", 0));
  }
}

Course::~Course()
{
}
void Course::setGrades(const std::map<std::string, double>& new_grades)
{
  grades = new_grades;
}
void Course::setScale(const std::map<std::string,double>& the_scale)
{
  if(type == 3){
    scale = the_scale;
  }
}
void Course::setPassThreshold(double thresh)
{
  if(type == 1){
    threshold = thresh;
  }
}
void Course::outputGrades()
{
  std::map<std::string, double>::iterator it;
  cout << courseName << ":" << endl;
  for(it = grades.begin(); it != grades.end(); ++it){
    if(type == 1){
      if(it->second >= threshold){
	cout << "\t" << it->first << " : " << "P" << endl;
      }
      else {
	cout << "\t" << it->first << " : " << "NP" << endl;
      }
    }
    else if(type == 2 || type == 3) {
      std::string letters[] = {"A", "B", "C", "D", "F"};
      for(unsigned i = 0; i < 5; i++){
	if(it->second >= scale[letters[i]]){
	  cout << "\t" << it->first << " : " << letters[i] << endl;
	  break;
	}
      }

    }
  }
  cout << endl;
}

int main()
{
  map<string, double> students = { { "Jill", 100 },
				   { "Tommy", 87 },
				   { "Billy", 55 },
				   { "Diane", 71 } };
  map<string, double> custom_scale = { { "A", 85 },
				       { "B", 75 },
				       { "C", 60 },
				       { "D", 50 },
				       { "F", 0 } };

  // This code may be altered when you redefine your class hierarchy
  Course c1("CS 100", 1);
  c1.setGrades(students);
  c1.setPassThreshold(70);

  Course c2("CS 103", 2);
  c2.setGrades(students);

  Course c3("CS 104", 3);
  c3.setGrades(students);
  c3.setScale(custom_scale);

  // This code should not need to be altered when you redefine your
  // class hierarchy
  vector<Course*> courses = { &c1, &c2, &c3 };
  for(unsigned i = 0; i < courses.size(); i++){
    courses[i]->outputGrades();
  }
  
  return 0;
}
