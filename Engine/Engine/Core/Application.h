#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Renderer.h"
#include "Timer.h"
#include "AudioManager.h"
#include "AssetManager.h"

class Application
{
public:
	Application();
	~Application();

	Renderer * renderer;
	AssetManager* assetMan;
	// Printing fps
	static Timer Time;

	AudioManager masterBG;

	// Initialize core engine systems and resources
	void Init();

	// Start the engine
	void Run();

	// Cleanup for program exit
	void Exit();
};

#endif