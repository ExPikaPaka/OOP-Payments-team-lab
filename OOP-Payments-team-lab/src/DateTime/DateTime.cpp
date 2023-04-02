#include "DateTime.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

bool DateTime::isValidTime(std::tm t) {
		std::time_t time = std::mktime(&t);
		return time != -1;
}

DateTime::DateTime() {
	time = {};
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&time, &t);
}

DateTime::DateTime(std::chrono::system_clock::time_point time_point) {
	setTime(time_point);
}

DateTime::DateTime(std::tm time_point) {
	setTime(time_point);
}

void DateTime::setTime(std::chrono::system_clock::time_point time_point) {
	std::time_t t = std::chrono::system_clock::to_time_t(time_point);
	std::tm temp;
	localtime_s(&temp, &t);

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setTime(std::tm time_point) {
	if (!isValidTime(time_point)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = time_point;
}

std::tm DateTime::getTime() {
	return time;
}

void DateTime::setMon(int value) {
	std::tm temp = time;
	temp.tm_mon = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setYear(int value) {
	std::tm temp = time;
	temp.tm_year = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setWDay(int value) {
	std::tm temp = time;
	temp.tm_wday = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setYDay(int value) {
	std::tm temp = time;
	temp.tm_yday = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setSec(int value) {
	std::tm temp = time;
	temp.tm_sec = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setMin(int value) {
	std::tm temp = time;
	temp.tm_min = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setHour(int value) {
	std::tm temp = time;
	temp.tm_hour = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

void DateTime::setMDay(int value) {
	std::tm temp = time;
	temp.tm_mday = value;

	if (!isValidTime(temp)) {
		throw(std::invalid_argument("Invalid time!"));
	}
	time = temp;
}

std::string DateTime::toString(char dateSeparator, char timeSeparator) {
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << time.tm_hour << timeSeparator
		<< std::setw(2) << time.tm_min << timeSeparator
		<< std::setw(2) << time.tm_sec << " "
		<< std::setw(2) << time.tm_mday << dateSeparator
		<< std::setw(2) << (time.tm_mon + 1) << dateSeparator // tm_mon is 0-based
		<< (time.tm_year + 1900);

	std::string formatted_time = ss.str();
	
	return formatted_time;
}
