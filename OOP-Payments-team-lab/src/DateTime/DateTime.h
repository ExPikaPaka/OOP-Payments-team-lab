#pragma once
#include <chrono>
#include <time.h>
class DateTime {
	int day;
	int month;
	int year;

	int second;
	int minute;
	int hour;

public:
	DateTime();
	DateTime(std::chrono::system_clock::time_point time_point);
};

