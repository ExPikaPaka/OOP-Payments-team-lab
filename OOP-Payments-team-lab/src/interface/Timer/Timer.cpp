#include <chrono>
#include "Timer.h"

Timer::Timer() {
	begin = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	previous = begin;
	end = begin;
	FPS = 60;
}

//411103623830200
//     ^
//  Second
bool Timer::isTimeUp() {
	if (begin >= previous + 1000000000.0 / (double)FPS) {
		return true;
	}
	return false;
}

void Timer::start() {
	begin = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Timer::stop() {
	end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Timer::next() {
	previous = end;
}

double Timer::elapsed() {
	return (double)(end - previous) / 1000.0 / 1000.0;
}

void Timer::setFPS(double value) {
	FPS = value;
}

double Timer::getFPS() {
	return 1'000'000'000.0 / (double)(end - previous);
}
#include <iostream>
void Timer::print() {
	std::cout << "Begin: " << begin << '\n';
	std::cout << "Previ: " << previous << '\n';
	std::cout << "End  : " << end << '\n';
}

