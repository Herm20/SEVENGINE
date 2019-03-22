#include "Application.h"

#include <boost/chrono/chrono.hpp>
#include <boost/thread/thread.hpp>

Application::Application()
{
	// Nothing interesting to do here (yet)
}


Application::~Application()
{
	// Nothing interesting to do here (yet)
}

void Application::Init()
{
	renderer = new Renderer;
	printf("INIT\n");
}

void Application::Run()
{
	// Making it "true" for now
	while (true)
	{
		// Update objects, process input, draw objects to the screen, et cetera
		boost::this_thread::sleep_for(boost::chrono::milliseconds(250));
		//printf("TEST\n");
		renderer->Draw();
	}
}

void Application::Exit()
{
	delete renderer;
	printf("END\n");
}
