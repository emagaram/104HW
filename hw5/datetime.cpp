#include "datetime.h"
#include <ctime>
#include <string>
std::string convertTwoDigitInt(int i)
{
	std::string s = "";
	if (i <= 9)
	{
		s += "0";
	}
	s += std::to_string(i);
	return s;
}

DateTime::DateTime()
{
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int year = timeinfo->tm_year;
	year += 1900;
	hour = timeinfo->tm_hour;
	min = timeinfo->tm_min;
	sec = timeinfo->tm_sec;
	this->year = year;
	this->month = timeinfo->tm_mon + 1;
	this->day = timeinfo->tm_mday;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
	hour = hh;
	min = mm;
	sec = ss;
	this->year = year;
	this->month = month;
	this->day = day;
}

bool DateTime::operator<(const DateTime &other) const
{
	//Could've used a map but doesn't really matter
	int thisTimes[6] = {year, month, day, hour, min, sec};
	int otherTimes[6] = {other.year, other.month, other.day, other.hour, other.min, other.sec};
	for (int i = 0; i < 6; i++)
	{
		if (thisTimes[i] < otherTimes[i])
		{
			return true;
		}
		else if (otherTimes[i] < thisTimes[i])
		{
			return false;
		}
	}

	//Will only get called if they are equal
	return false;
}

std::ostream &operator<<(std::ostream &os, const DateTime &other)
{
	os << other.year << "-" << convertTwoDigitInt(other.month) << "-" << convertTwoDigitInt(other.day) << " "
	   << convertTwoDigitInt(other.hour) << ":" << convertTwoDigitInt(other.min) << ":" << convertTwoDigitInt(other.sec) << " ";

	return os;
}

//    * Inputs the timestamp from the given istream expecting the format:
//    *   YYYY-MM-DD HH:MM:SS
//    *  Returns if an error in the format with the DateTime set to the
//    *   current system time/date
//    *
//    *
//    * @return the istream passed in as an argument
//    */s
std::istream &operator>>(std::istream &is, DateTime &dt)
{
	std::string threeTimes;
	is >> threeTimes;
	try
	{
		dt.year = std::stoi(threeTimes.substr(0, 4));
		dt.month = std::stoi(threeTimes.substr(5, 2));
		dt.day = std::stoi(threeTimes.substr(8, 2));

		is >> threeTimes;
		dt.hour = std::stoi(threeTimes.substr(0, 2));
		dt.min = std::stoi(threeTimes.substr(3, 2));
		dt.sec = std::stoi(threeTimes.substr(6, 2));
	}
	catch (std::exception x)
	{
		DateTime k;
		dt = k;
	}
	return is;
	// TODO: insert return statement here
}
