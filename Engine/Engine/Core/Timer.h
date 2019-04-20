#ifndef TIMER_H_
#define TIMER_H_
#include <ctime>
#include <chrono>
class Timer
{
private:
	clock_t curr, prev;
	std::chrono::high_resolution_clock::time_point startTime;
	static float totalTime; //! Time in seconds since starting
	static float deltaTime; //! Time in seconds between 2 most recent updates
public:
	Timer();
	static float GetTotalTime();
	static float GetDeltaTime();
	void update();
	std::chrono::duration<float> currentTime();
};
#endif // TIMER_H_

