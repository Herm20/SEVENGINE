#include "Application.h"

#include <boost/chrono/chrono.hpp>
#include <boost/thread/thread.hpp>

Timer Application::Time;

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
	assetMan = new AssetManager();
	//ent = new Entity();
	renderer = new Renderer(assetMan);
	assetMan->LoadDirectory("Assets");
	Load();

	//TODO: Change this to dynamically create programs
	renderer->CreateBasicProgram();
	//masterBG.InitSound();
	//masterBG.LoadFile("audio/gameMusic.mp3");
	//masterBG.Play(false);
	printf("INIT\n");
}

void Application::Load()
{

}


void Application::Run()
{
	// Making it "true" for now
	while (true)
	{
		Time.update();

		printf("Time: %f", Time.fps);
		system("CLS");

		// Update objects, process input, draw objects to the screen, et cetera
		boost::this_thread::sleep_for(boost::chrono::milliseconds(250));
		renderer->Draw();
	}
}

void Application::Exit()
{
	delete assetMan;
	delete renderer;
	printf("END\n");
}


