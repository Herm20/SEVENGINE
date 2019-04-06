#ifndef TIMER_H_
#define TIMER_H_
//#include <Windows.h>
//#include <sstream>
#include <ctime>

class Timer
{
private:
	clock_t curr, prev;

public:
	Timer();

	float t; //Time in seconds since starting
	float dt; // Time in seconds between 2 most recent updates
	float fps; // Measures 1/dt the amount of updates per second

	void update();
	void updateTitleBar(char* _gameName, int winWidth, int winHeight);
};
#endif // TIMER_H_

