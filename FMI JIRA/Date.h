#pragma once
#include <iostream>

class Date {
	int day;
	int month;
	int year;
public:
	Date(int day, int month, int year);
	static bool isLeapYear(int year);
	static int maxDaysInMonth(int month, int year);
	static Date parse(const std::string& dateStr);
	static Date today();
	static Date addDays(const Date& date, int days);

	std::strong_ordering operator <=>(const Date& other) const {
		if (auto cmp = year <=> other.year; cmp != 0) return cmp;
		if (auto cmp = month <=> other.month; cmp != 0) return cmp;
		return day <=> other.day;
	}

	bool operator==(const Date& other) const = default;

	std::string getDate() const;
};