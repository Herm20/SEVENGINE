#include "Timer_Sad.h"

Timer* Timer::instance;
Timer::Timer()
{
	startTime = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() 
{
	delete instance;
}

void Timer::Init() 
{

}

std::chrono::duration<float> Timer::GetCurrentTime()
{
	using namespace std;
	auto time = chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = time - startTime;
	return duration;
}
