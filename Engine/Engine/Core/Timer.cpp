#include "Timer.h"

////High Res clock version//////////////

//static declarations
TimeDuration Timer::deltaTime;
TimePoint Timer::curr = SteadyClock::now();
TimePoint Timer::prev = Timer::curr;
TimePoint Timer::startTime = Timer::curr;
float Timer::dt; 
double Timer::current = glfwGetTime(), Timer::previous;
float Timer::tt = 0;

void Timer::update()
{
	/*prev = curr;
	curr = SteadyClock::now();;
	deltaTime = curr - prev;
	dt = (float)deltaTime.count();*/

	previous = current;
	current = glfwGetTime();
	dt = (float)(current - previous);

	tt += dt;
}

float Timer::GetTotalTime()
{
	return tt;
}

float Timer::GetDeltaTime()
{
	return dt;
}

TimeDuration Timer::currentTime()
{
	using namespace std;
	auto time = HighClock::now();
	TimeDuration duration = time - startTime;
	return duration;
}

