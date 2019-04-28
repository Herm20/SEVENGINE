#include "Application.h"

#include "ECS/System.h"

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
	Logger::Log(Logger::LogType::MSG, "Initializing engine");
	renderer = new Renderer(manager);
	assetMan = new AssetManager();
	eventMan = new EventManager();

	lightSystem = new LightSystem(manager);
	lightSystem->SetLightsVector(&renderer->GetLightVector());
	scriptSystem = new ScriptSystem(manager, assetMan);
	scriptSystem->Init();

	cameraSystem = new CameraSystem(manager);
	cameraSystem->Init(renderer->GetWindow());

	renderer->SetCurrentCamera(cameraSystem);

	inputPoller.Init(renderer->GetWindow());

	assetMan->SetAssetDir("Assets");
	assetMan->LoadAssetsFromAssetDir();
	assetMan->CreateMaterial("default", assetMan->GetTexture("defaultAlbedo"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	assetMan->CreateMaterial("test", assetMan->GetTexture("test"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));

	masterBG = new AudioManager();
	masterBG->InitSoundBG();
	masterBG->LoadBGFile("Assets/Audio/Background/gameMusic.mp3");
	masterBG->Play();
	masterBG->SetVolume(0.08f);

	masterEffect = new AudioManager();
	masterEffect->InitSoundEffect();

	manager.createComponentStore<ecs::MeshRendererComponent>();
	manager.createComponentStore<ecs::TransformComponent>();
	manager.createComponentStore<ecs::KeyboardInputComponent>();
	manager.createComponentStore<ecs::PlayerStateInfoComponent>();
	manager.createComponentStore<ecs::RigidBodyComponent>();
	manager.createComponentStore<ecs::LightComponent>();
	manager.createComponentStore<ecs::ScriptComponent>();

	// Systems will run in the order they are added
	manager.addSystem(ecs::System::Ptr(new PlayerControllerSystem(manager)));
	manager.addSystem(ecs::System::Ptr(new RigidBodySystem(manager)));
	manager.addSystem(ecs::System::Ptr(lightSystem));
	manager.addSystem(ecs::System::Ptr(renderer));
	manager.addSystem(ecs::System::Ptr(scriptSystem));

	ecs::Entity gm = manager.createEntity();
	manager.addComponent(gm, ecs::TransformComponent());
	manager.addComponent(gm, ecs::ScriptComponent());
	ecs::ScriptComponent& scriptComp2 = manager.getComponentStore<ecs::ScriptComponent>().get(gm);

	scriptComp2.path = boost::container::string("Assets/Scripts/game-manager.lua");
	manager.registerEntity(gm);

	reloadHeld = false;
}

void Application::Load()
{

}

void Application::Run()
{
	// Init mouse to center of screen
	int w = renderer->GetWindowWidth();
	int h = renderer->GetWindowHeight();
	glfwSetCursorPos(renderer->GetWindow(), w * .5f, h * .5f);

	// Game loop
	while (!glfwWindowShouldClose(renderer->GetWindow()) && !Input::GetKey(GLFW_KEY_ESCAPE))
	{
		Timer::update();

		cameraSystem->Update(renderer->GetWindowWidth(), renderer->GetWindowHeight());
		cameraSystem->Movement(renderer->GetWindow(),renderer->GetWindowWidth(), renderer->GetWindowHeight());
		
		EventManager::ExecuteNext();

		if (Input::GetKey(GLFW_KEY_P))
		{
			if (!reloadHeld) { scriptSystem->ReloadScripts(); }
			reloadHeld = true;
		}
		else { reloadHeld = false; }

		manager.updateEntities(Timer::GetDeltaTime());

		glfwPollEvents();
	}
}

void Application::Exit()
{
	assetMan->SaveAssets();
	Logger::Log(Logger::LogType::MSG, "Exiting engine");
	boost::container::string name = Logger::GetFormatedSystemTime();
	name += "-log.txt";
	assetMan->SaveAssetToFile("Log", name.c_str(), Logger::GetLog());
	delete eventMan;
	delete assetMan;
}
