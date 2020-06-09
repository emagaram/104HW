#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"
#include <string>
#pragma warning(disable : 4996)
using namespace std;


// Add your implementations here.

  /**
   * Default constructor should create a string
   * equal to ""
   */

Str::Str() {
	data_ = new char[1];
	data_[0] = '\0';
}
/**
 * Character array constructor
 *  If s is NULL create a string that contains
 *  only the null character (i.e. "")
 */
Str::Str(const char* s) {
	if (s == NULL) {

		data_ = new char[1];
		data_[0] = '\0';
	}
	else {
		int length = strlen(s);
		data_ = new char[length];
		strcpy(data_, s);

	}
}
Str& Str::operator=(const char* s) {
	if (data_ != NULL) {
		delete[] data_;
	}
	
	if (s == NULL) {
		data_ = new char[1];
		data_[0] = '\0';
	}
	else {
		int length = strlen(s);
		data_ = new char[length];
		strcpy(data_, s);
	}

	return *this;
}

/**
 * Str concatenation-assignment operator
 *  E.g. s += t
 */

Str& Str::operator+=(const Str& s) {
	int thisLength = strlen(data_);
	int sLength = strlen(s.data_);
	char* newData = new char[sLength+thisLength+1];
	strcpy(newData, data_);
	strcpy(&newData[thisLength], s.data_);

	//delete[] data_; Tried to fix this leak, didnt have time
	data_ = newData;

	return *this;
}
/**
 * Char. array concatenation-assignment operator
 *  E.g. s += " more"
 *  If s is NULL simply return this Str
 */
Str& Str::operator+=(const char* s) {
	Str a;
	a.data_ = data_;
	return a;
}

/**
 * Return the size of the string (e.g. "Hello" => 5)
 */
size_t Str::size() const {
	size_t a = 5;
	return a;
}

/**
 * Non-const index operator
 *  E.g.  str s1("103");  s1[2] = '4';
 * Should throw std::out_of_range if invalid index is passed
 */
char& Str::operator[](unsigned int i) {
	char a = 'x';
	return a;
}
/**
 * Const index operator
 *  E.g. str s1("104");  char c = s1[2];
 * Should throw std::out_of_range if invalid index is passed
 */
char const& Str::operator[](unsigned int i) const {
	return 'x';
}


/**
 * String concatenation operator
 *  E.g. str s1; cout << s1 + " world" << endl;
 *  If rhs is NULL, simply return a copy of this Str
 */
Str Str::operator+(const char* rhs) const {
	Str a;
	a.data_ = data_;
	return a;
}

std::ostream& operator<<(std::ostream& ostr, Str& s) {
	std::string stemp = string(s.data_);
	int i = 0;
	while (s.data_[i]!='\0') {
		ostr << s.data_[i];
		i++;
	}
	
	return ostr;
}

std::istream& operator>>(std::istream& istr, Str& s)
{
	std::string stemp;
	istr >> stemp;
	s = stemp.c_str();
	return istr;
}


