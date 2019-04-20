#include "Timer.h"

float Timer::totalTime = 0;
float Timer::deltaTime = 0;

Timer::Timer()
{
	startTime = std::chrono::high_resolution_clock::now();
	prev = curr = clock();
}

void Timer::update()
{
	prev = curr;
	curr = clock();
	deltaTime = (float)(curr - prev) / (float)CLOCKS_PER_SEC;

	// Testing a bottom cap of the dt
	if (deltaTime < 0.01f) 
	{
		deltaTime = 0.01f;
	}

	totalTime += deltaTime;
}

float Timer::GetTotalTime()
{
	return totalTime;
}

float Timer::GetDeltaTime()
{
	return deltaTime;
}

std::chrono::duration<float> Timer::currentTime()
{
	using namespace std;
	auto time = chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = time - startTime;
	return duration;
}
