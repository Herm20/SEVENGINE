#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <map>
#include "Renderer.h"
#include "Timer.h"
#include "AudioManager.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Logger.h"
#include "ECS/Manager.h"
#include "EventManager.h"

class Application
{
public:
	Application();
	~Application();

	ecs::Manager manager;

	Renderer* renderer;
	AssetManager* assetMan;
	EventManager* eventMan;
	Camera* camera;
	// Printing fps
	static Timer Time;

	ecs::Entity e1;
	ecs::Entity e2;

	AudioManager* masterBG;
	AudioManager* masterEffect;

	// Initialize core engine systems and resources
	void Init();

	// Start the engine
	void Run();

	// Cleanup for program exit
	void Exit();

	// Load Assets
	void Load();

	/// SUPER TEMP
	void InitKeyCallbacks();
	void CamMovement();
	/// SUPER TEMP
};

#endif
