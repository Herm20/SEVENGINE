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
	scriptSystem = new ScriptSystem(manager);
	scriptSystem->Init();
	renderer = new Renderer(manager);
	assetMan = new AssetManager();
	eventMan = new EventManager();

	lightSystem = new LightSystem(manager);
	lightSystem->SetLightsVector(&renderer->GetLightVector());

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

	// Dummy Player Entity
	player1 = manager.createEntity();
	manager.addComponent(player1, ecs::MeshRendererComponent());
	manager.addComponent(player1, ecs::TransformComponent());
	manager.addComponent(player1, ecs::KeyboardInputComponent());
	manager.addComponent(player1, ecs::PlayerStateInfoComponent());
	manager.addComponent(player1, ecs::RigidBodyComponent());
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(player1);
	meshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sword")));
	meshRenderer.material = assetMan->GetMaterial("test");
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(player1);
	transform.transform.SetPosition(glm::vec3(0, 0, 0));
	manager.registerEntity(player1);
	ecs::KeyboardInputComponent& keyboardInput = manager.getComponentStore<ecs::KeyboardInputComponent>().get(player1);
	keyboardInput.map["Jump"] = GLFW_KEY_UP;
	keyboardInput.map["MoveLeft"] = GLFW_KEY_LEFT;
	keyboardInput.map["MoveRight"] = GLFW_KEY_RIGHT;

	e2 = manager.createEntity();
	manager.addComponent(e2, ecs::TransformComponent());
	manager.getComponentStore<ecs::TransformComponent>().get(e2).transform.SetRotation(glm::angleAxis(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	manager.addComponent(e2, ecs::LightComponent());
	//ecs::LightComponent & light = manager.getComponentStore<ecs::LightComponent>().get(player1);
	//light.light.color = (glm::vec3(0, 5, -1));
	manager.registerEntity(e2);

	se = manager.createEntity();
	manager.addComponent(se, ecs::TransformComponent());
	manager.addComponent(se, ecs::MeshRendererComponent());
	manager.addComponent(se, ecs::ScriptComponent());
	ecs::MeshRendererComponent& seRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(se);
	seRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("box")));
	seRenderer.material = assetMan->GetMaterial("test");
	ecs::ScriptComponent& scriptComp = manager.getComponentStore<ecs::ScriptComponent>().get(se);
	scriptComp.path = boost::container::string("Assets/Scripts/test-object.lua\0");
	manager.registerEntity(se);

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
