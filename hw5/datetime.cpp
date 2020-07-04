#include "datetime.h"
#include <ctime>
DateTime::DateTime()
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int year = timeinfo->tm_year;
	year += 1900;
	hour=timeinfo->tm_hour;
	min=timeinfo->tm_min;
	sec=timeinfo->tm_sec;
	this->year=year;
	this->month=timeinfo->tm_mon+1;
	this->day=timeinfo->tm_mday;		
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
	hour=hh;
	min=mm;
	sec=ss;
	this->year=year;
	this->month=month;
	this->day=day;
	
}

bool DateTime::operator<(const DateTime& other) const
{
	//Could've used a map but doesn't really matter
	int thisTimes[6]  = {year, month, day, hour, min,sec};
	int otherTimes[6] = {other.year, other.month, other.day, other.hour, other.min, other.sec};
	for(int i = 0; i<6;i++){
		if(thisTimes[i] < otherTimes[i]){
			return true;
		}
		else if(otherTimes[i] < thisTimes[i]){
			return false;
		}
	}

	
	//Will only get called if they are equal
	return false;
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
	// TODO: insert return statement here
	return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
	return is;
	// TODO: insert return statement here
}
