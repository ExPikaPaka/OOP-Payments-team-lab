#include "DateTime.h"

DateTime::DateTime() {
	day = 0;
	month = 0;
	year = 0;
	second = 0;
	minute = 0;
	hour = 0;
	day = 0;
}

DateTime::DateTime(std::chrono::system_clock::time_point time_point) {
	std::time_t t = std::chrono::system_clock::to_time_t(time_point);
	std::tm tm;

	localtime_s(&tm, &t);

	day = tm.tm_mday;
	month = tm.tm_mon;
	year = tm.tm_year;
	second = tm.tm_sec;
	minute = tm.tm_min;
	hour = tm.tm_hour;
	day = tm.tm_mday;
}
