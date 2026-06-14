#include "Date.h"
#include <vector>
#include <sstream>
#include <ctime>

Date::Date(int day, int month, int year): day(day), month(month), year(year)
{
	if (year < 0) throw std::invalid_argument("The year cannot be negative number.");
	if (month < 1 || month > 12) throw std::invalid_argument("Invalid month.");
	if (day < 1 || day > maxDaysInMonth(month, year)) throw std::invalid_argument("Invalid day.");
}

bool Date::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::maxDaysInMonth(int month, int year)
{
	static const std::vector<int> days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isLeapYear(year)) return 29;
	return days[month - 1];
}

Date Date::parse(const std::string& dateStr)
{
	int day, month, year;
	char sep1, sep2;

	std::istringstream stream(dateStr);
	stream >> day >> sep1 >> month >> sep2 >> year;

	if (stream.fail() || sep1 != '/' || sep2 != '/') {
		throw std::invalid_argument("Invalid date format. Use dd/mm/yyyy.");
	}

	return Date(day, month, year);
}

Date Date::today()
{
	time_t t = time(nullptr);
	tm now{};
	localtime_s(&now, &t);
	return Date(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
}

Date Date::addDays(const Date& date, int days)
{
	tm t = {};
	t.tm_mday = date.day + days;
	t.tm_mon = date.month - 1;
	t.tm_year = date.year - 1900;

	mktime(&t);

	return Date(t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);
}

std::string Date::getDate() const
{
	return std::format("{:02}/{:02}/{}", day, month, year);
}
