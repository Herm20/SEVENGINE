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
	Logger::Log(Logger::LogType::MSG, "Init session");
	assetMan = new AssetManager();
	renderer = new Renderer(assetMan);
	assetMan->SetAssetDir("Assets");
	assetMan->LoadAssetsFromAssetDir();

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
	assetMan->SaveAssets();
	Logger::Log(Logger::LogType::MSG, "End session");
	std::string name = Logger::GetFormatedSystemTime();
	name += "-log.txt";
	assetMan->SaveAssetToFile("Log", name.c_str(), Logger::GetLog());
	delete assetMan;
	delete renderer;
}
