#include "datetime.h"

DateTime::DateTime()
{
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
}

bool DateTime::operator<(const DateTime& other) const
{
	return false;
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
	// TODO: insert return statement here
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
	// TODO: insert return statement here
}
