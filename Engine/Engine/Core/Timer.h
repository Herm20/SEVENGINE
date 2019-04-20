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

	void update();
	std::chrono::duration<float> currentTime();
};
#endif // TIMER_H_

