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
	Logger::Log(Logger::LOGTYPE::MSG, "Init session");
	assetMan = new AssetManager();
	renderer = new Renderer(assetMan);
	assetMan->LoadDirectory("Assets");

	//TODO: Change this to dynamically create programs
	renderer->CreateBasicProgram();
	//masterBG.InitSound();
	//masterBG.LoadFile("audio/gameMusic.mp3");
	//masterBG.Play(false);
}

void Application::Run()
{
	// Making it "true" for now
	while (!renderer->ShouldClose())
	{
		Time.update();

		//printf("Time: %f", Time.fps);

#if defined _WIN32
		system("CLS");
#elif defined __unix__
		system("clear");
#endif
		// Update objects, process input, draw objects to the screen, et cetera
		boost::this_thread::sleep_for(boost::chrono::milliseconds(250));
		renderer->Draw();
	}
}

void Application::Exit()
{
	Logger::Log(Logger::LOGTYPE::MSG, "End session");
	assetMan->SaveAssetToFile("Log", "log.txt", Logger::GetLog());
	assetMan->SaveAssets();
	delete assetMan;
	delete renderer;
}
