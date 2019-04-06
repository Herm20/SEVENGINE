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

void Timer::updateTitleBar(char* _gameName, int winWidth, int winHeight)
{
	/*std::ostringstream output;
	output.precision(6);
	output << _gameName <<
		"	Width: " << winWidth <<
		"	Height: " << winHeight <<
		"	FPS: " << fps <<
		"	Delta Time: " << dt;

	//SetWindowText(hWnd, output.str().c_str());*/
}
