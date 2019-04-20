#include "Timer.h"

Timer::Timer()
{
	startTime = std::chrono::high_resolution_clock::now();
	prev = curr = clock();
	t = dt = 0;
}

void Timer::update()
{
	prev = curr;
	curr = clock();
	dt = (float)(curr - prev) / (float)CLOCKS_PER_SEC;

	// Testing a bottom cap of the dt
	if (dt < 0.01f) 
	{
		dt = 0.01f;
	}

	t += dt;
}

std::chrono::duration<float> Timer::currentTime()
{
	using namespace std;
	auto time = chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = time - startTime;
	return duration;
}
