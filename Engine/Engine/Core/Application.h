#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Renderer.h"

class Application
{
public:
	Application();
	~Application();

	Renderer * renderer;

	// Initialize core engine systems and resources
	void Init();

	// Start the engine
	void Run();

	// Cleanup for program exit
	void Exit();
};

#endif