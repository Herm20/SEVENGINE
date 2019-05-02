#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Renderer.h"
#include "AudioManager.h"
#include "AssetManager.h"
#include "Logger.h"
#include "ECS/Manager.h"
#include "EventManager.h"
#include "ComboManager.h"

// Systems
#include "Systems/PlayerControllerSystem.h"
#include "Systems/RigidBodySystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/LightSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/Camera.h"

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
	LightSystem* lightSystem;
	ScriptSystem* scriptSystem;
	CameraSystem* cameraSystem;

	// Printing fps
	static Timer Time;

	ecs::Entity player1;
	ecs::Entity e2;
	ecs::Entity se;

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

	//comboTester
	void TestingCombo();

	//variables for testing combo
	std::map<std::string, int> keys;
	ComboManager* combo;

	//Create a player
	void CreatePlayer(glm::vec3 pos, int leftKey, int rightKey, int jumpKey);
};

#endif
