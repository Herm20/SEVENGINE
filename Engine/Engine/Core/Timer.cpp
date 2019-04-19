#include "Timer.h"

Timer::Timer()
{
	prev = curr = clock();
	t = dt = fps = 0;
}

void Timer::update()
{
	prev = curr;
	curr = clock();
	dt = (curr - prev) / (float)CLOCKS_PER_SEC;
	t += dt;
	fps = 1 / dt;
}

std::chrono::duration<float> currentTime()
{
	//using namespace std;
	//auto time = chrono::high_resolution_clock::now();
	////std::chrono::duration<float> duration = time - startTime;
	//return duration;
}
