#ifndef TIMER_H_
#define TIMER_H_
#include <ctime>
#include <chrono>
class Timer
{
private:
	clock_t curr, prev;
	std::chrono::high_resolution_clock::time_point startTime;
public:
	Timer();

	float t; //Time in seconds since starting
	float dt; // Time in seconds between 2 most recent updates
	float fps; // Measures 1/dt the amount of updates per second

	void update();
	//std::chrono::duration<float> currentTime();
};
#endif // TIMER_H_

