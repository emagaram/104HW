#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Course
{
public:
  Course(std::string name);
  ~Course();
  // Public method useful for all types of Courses
  void setGrades(const std::map<std::string, double> &new_grades);

  // All courses must be able to output the students and their grades
  // by calling a member function with this signature
  virtual void outputGrades() = 0;

protected:
  std::string courseName;               // 1 = Pass/NoPass, 2 = straight scale, 3=Custom scale
  std::map<std::string, double> grades; // map student names to numeric total
};

Course::Course(std::string name)
{
  courseName = name;
  // if (type == 2 || type == 3)
  // {
  //   // Scale to be used for type 2 (Straight scale) courses and
  //   // Default scale for type 3 = Custom scale that can
  //   // be replaced by a call to setScale()
  //   scale.insert(std::make_pair("A", 90));
  //   scale.insert(std::make_pair("B", 80));
  //   scale.insert(std::make_pair("C", 70));
  //   scale.insert(std::make_pair("D", 60));
  //   scale.insert(std::make_pair("F", 0));
  // }
}

Course::~Course()
{
}

void Course::setGrades(const std::map<std::string, double> &new_grades)
{
  grades = new_grades;
}
// void Course::outputGrades()
// {
//   std::map<std::string, double>::iterator it;
//   cout << courseName << ":" << endl;
//   for(it = grades.begin(); it != grades.end(); ++it){
//     if(type == 1){
//       if(it->second >= threshold){
// 	cout << "\t" << it->first << " : " << "P" << endl;
//       }
//       else {
// 	cout << "\t" << it->first << " : " << "NP" << endl;
//       }
//     }
//     else if(type == 2 || type == 3) {
//       std::string letters[] = {"A", "B", "C", "D", "F"};
//       for(unsigned i = 0; i < 5; i++){
// 	if(it->second >= scale[letters[i]]){
// 	  cout << "\t" << it->first << " : " << letters[i] << endl;
// 	  break;
// 	}
//       }
//     }
//   }
//   cout << endl;
// }
class CustomScale : public Course
{
public:
  CustomScale(std::string name);
  void setScale(const std::map<std::string, double> &the_scale);
  void outputGrades()
  {
    std::map<std::string, double>::iterator it;
    cout << courseName << ":" << endl;
    for (it = grades.begin(); it != grades.end(); ++it)
    {
      std::string letters[] = {"A", "B", "C", "D", "F"};
      for (unsigned i = 0; i < 5; i++)
      {
        if (it->second >= scale[letters[i]])
        {
          cout << "\t" << it->first << " : " << letters[i] << endl;
          break;
        }
      }
    }
    cout << endl;
  }

private:
  std::map<std::string, double> scale; // map letter grade to lower bound
};

void CustomScale::setScale(const std::map<std::string, double> &the_scale)
{
  scale.insert(std::make_pair("A", 85.5));
  scale.insert(std::make_pair("B", 72.0));
  scale.insert(std::make_pair("C", 65.75));
  scale.insert(std::make_pair("D", 60));
  scale.insert(std::make_pair("F", 0));
}

CustomScale::CustomScale(std::string name) : Course(name)
{
  scale.insert(std::make_pair("A", 90));
  scale.insert(std::make_pair("B", 80));
  scale.insert(std::make_pair("C", 70));
  scale.insert(std::make_pair("D", 60));
  scale.insert(std::make_pair("F", 0));
}
class StraightScale : public Course
{
public:
  StraightScale(std::string name);

  void outputGrades()
  {
    std::map<std::string, double>::iterator it;
    cout << courseName << ":" << endl;
    for (it = grades.begin(); it != grades.end(); ++it)
    {
      std::string letters[] = {"A", "B", "C", "D", "F"};
      for (unsigned i = 0; i < 5; i++)
      {
        if (it->second >= scale[letters[i]])
        {
          cout << "\t" << it->first << " : " << letters[i] << endl;
          break;
        }
      }
    }
    cout << endl;
  }

private:
  std::map<std::string, double> scale; // map letter grade to lower bound
};

StraightScale::StraightScale(std::string name) : Course(name)
{
  scale.insert(std::make_pair("A", 90));
  scale.insert(std::make_pair("B", 80));
  scale.insert(std::make_pair("C", 70));
  scale.insert(std::make_pair("D", 60));
  scale.insert(std::make_pair("F", 0));
}

class PassNoPass : public Course
{

public:
  void setPassThreshold(double thresh);
  PassNoPass(std::string name);

  void outputGrades()
  {
    std::map<std::string, double>::iterator it;
    cout << courseName << ":" << endl;
    for (it = grades.begin(); it != grades.end(); ++it)
    {
      if (it->second >= threshold)
      {
        cout << "\t" << it->first << " : "
             << "P" << endl;
      }
      else
      {
        cout << "\t" << it->first << " : "
             << "NP" << endl;
      }
    }
    cout << endl;
  }

private:
  double threshold;
};

PassNoPass::PassNoPass(std::string name) : Course(name)
{
}

void PassNoPass::setPassThreshold(double thresh)
{
  threshold = thresh;
}

int main()
{

  //NOTE: I realize I should have made a second class that straightscale and custom inherited from since there
  //was a lot of repition but I did not have time. Maybe I'll get to it later
  map<string, double> students = {{"Jill", 100},
                                  {"Tommy", 87},
                                  {"Billy", 55},
                                  {"Diane", 71}};
  map<string, double> custom_scale = {{"A", 85},
                                      {"B", 75},
                                      {"C", 60},
                                      {"D", 50},
                                      {"F", 0}};

  // This code may be altered when you redefine your class hierarchy
  PassNoPass c1("CS 100");
  c1.setGrades(students);
  c1.setPassThreshold(70);

  StraightScale c2("CS 103");
  c2.setGrades(students);

  CustomScale c3("CS 104");
  c3.setGrades(students);
  c3.setScale(custom_scale);

  // This code should not need to be altered when you redefine your
  // class hierarchy
  vector<Course *> courses = {&c1, &c2, &c3};
  for (unsigned i = 0; i < courses.size(); i++)
  {
    courses[i]->outputGrades();
  }

  return 0;
}
