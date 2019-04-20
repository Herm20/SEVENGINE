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
#include "InputPoller.h"

// Systems
#include "Systems/PlayerControllerSystem.h"
#include "Systems/RigidBodySystem.h"

class Application
{
public:
	Application();
	~Application();

	ecs::Manager manager;

	Input inputPoller;

	Renderer* renderer;
	AssetManager* assetMan;
	Camera* camera;
	// Printing fps
	static Timer Time;

	ecs::Entity player1;
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
