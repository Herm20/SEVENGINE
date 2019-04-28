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
#include "EventManager.h"

// Systems
#include "Systems/PlayerControllerSystem.h"
#include "Systems/RigidBodySystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/LightSystem.h"
#include "Systems/ScriptSystem.h"

class Application
{
public:
	Application();
	~Application();

	ecs::Manager manager;

	Input inputPoller;

	Renderer* renderer;
	AssetManager* assetMan;
	EventManager* eventMan;
	Camera* camera;
	LightSystem* lightSystem;
	ScriptSystem* scriptSystem;
	// Printing fps
	static Timer Time;

	AudioManager* masterBG;
	AudioManager* masterEffect;

	bool reloadHeld;

	// Initialize core engine systems and resources
	void Init();

	// Start the engine
	void Run();

	// Cleanup for program exit
	void Exit();

	// Load Assets
	void Load();

	/// SUPER TEMP
	void CreatePlayer(glm::vec3 pos, int leftKey, int rightKey, int jumpKey);
	void CamMovement();
	/// SUPER TEMP
};

#endif
