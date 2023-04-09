#pragma once
class Timer {
	long long begin;
	long long previous;
	long long end;
	double FPS;
public:

	Timer();

	bool isTimeUp();
	void start();
	void stop();
	void next();

	// Returns elapsed time in ms
	double elapsed();

	void setFPS(double value);
	double getFPS();

	void print();
};

