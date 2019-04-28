#ifndef TIMER_H_
#define TIMER_H_
#include <ctime>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::duration<float> TimeDuration;
typedef std::chrono::high_resolution_clock  HighClock;
typedef std::chrono::steady_clock SteadyClock;

class Timer
{
private:
	static TimePoint curr, prev, startTime;
	static TimeDuration deltaTime;
	static float dt, tt;
	static double current, previous;

public:
	static float GetTotalTime();
	static float GetDeltaTime();
	static void update();
	static TimeDuration currentTime();
};

#endif // TIMER_H_