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
