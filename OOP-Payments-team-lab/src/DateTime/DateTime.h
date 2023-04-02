#pragma once
#include <chrono>
#include <ctime>
#include <string>

// Custom DatTime class
// It has checks if a given time is valid
// In case time is invalid throws std::invalid_argument("InvalidTime!"
class DateTime {
	std::tm time;

	bool isValidTime(std::tm t);
public:
	DateTime();
	DateTime(std::chrono::system_clock::time_point time_point);
	DateTime(std::tm time_point);

	void setTime(std::chrono::system_clock::time_point time_point);
	void setTime(std::tm time_point);
	std::tm getTime();

	void setSec(int value);
	void setMin(int value);
	void setHour(int value);
	void setMDay(int value);
	// 0 Based month
	void setMon(int value);
	// Year since 1900
	void setYear(int value);
	void setWDay(int value);
	void setYDay(int value);

	std::string toString(char dateSeparator = '.', char timeSeparator = ':');
};

