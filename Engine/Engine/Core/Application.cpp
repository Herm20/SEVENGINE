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
	assetMan->SetAssetDir("Assets");
	assetMan->LoadAssetsFromAssetDir();
	assetMan->CreateMaterial("default", assetMan->GetTexture("defaultAlbedo"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	assetMan->CreateMaterial("test", assetMan->GetTexture("test"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	assetMan->CreateMaterial("spritesheetp1", assetMan->GetTexture("NewspiderSheet"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("spritesheetp1"));
	assetMan->CreateMaterial("spritesheetp2", assetMan->GetTexture("NewspiderSheet"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("spritesheetp2"));
	assetMan->CreateMaterial("stage", assetMan->GetTexture("Stage_Texture"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	assetMan->CreateMaterial("redNoSpecular", assetMan->GetTexture("red"), assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("black"), assetMan->GetShaderProgram("def"));

	renderer->Init(assetMan);

	eventMan = new EventManager();

	lightSystem = new LightSystem(manager);
	lightSystem->SetLightsVector(&renderer->GetLightVector());

	cameraSystem = new CameraSystem(manager);
	cameraSystem->Init(renderer->GetWindow());

	scriptSystem = new ScriptSystem(manager, assetMan, cameraSystem);
	scriptSystem->Init();

	renderer->SetCurrentCamera(cameraSystem);

	inputPoller.Init(renderer->GetWindow());

	AudioManager::InitSoundBG();
	AudioManager::LoadBGFile("Assets/Audio/Background/upbeat.wav");
	AudioManager::Play();
	AudioManager::SetVolume(0.08f);

	AudioManager::InitSoundEffect();

	manager.createComponentStore<ecs::MeshRendererComponent>();
	manager.createComponentStore<ecs::TransformComponent>();
	manager.createComponentStore<ecs::KeyboardInputComponent>();
	manager.createComponentStore<ecs::PlayerStateInfoComponent>();
	manager.createComponentStore<ecs::RigidBodyComponent>();
	manager.createComponentStore<ecs::ColliderComponent>();
	manager.createComponentStore<ecs::LightComponent>();
	manager.createComponentStore<ecs::ScriptComponent>();
	manager.createComponentStore<ecs::SpriteSheetComponent>();

	// Systems will run in the order they are added
	manager.addSystem(ecs::System::Ptr(new PlayerControllerSystem(manager)));
	manager.addSystem(ecs::System::Ptr(new RigidBodySystem(manager)));
	manager.addSystem(ecs::System::Ptr(new CollisionSystem(manager, scriptSystem)));
	manager.addSystem(ecs::System::Ptr(lightSystem));
	manager.addSystem(ecs::System::Ptr(renderer));
	manager.addSystem(ecs::System::Ptr(scriptSystem));
	manager.addSystem(ecs::System::Ptr(new SpriteSheetSystem(manager)));

	ecs::Entity gm = manager.createEntity();
	manager.addComponent(gm, ecs::TransformComponent());
	manager.addComponent(gm, ecs::ScriptComponent());
	ecs::ScriptComponent& scriptComp2 = manager.getComponentStore<ecs::ScriptComponent>().get(gm);

	scriptComp2.path = boost::container::string("Assets/Scripts/game-manager.lua");
	manager.registerEntity(gm);

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
		//cameraSystem->Movement(renderer->GetWindow(),renderer->GetWindowWidth(), renderer->GetWindowHeight());
		
		EventManager::ExecuteNext();

		if (Input::GetKeyDown(GLFW_KEY_P))
		{
			scriptSystem->ReloadScripts();
		}

		manager.updateEntities(Timer::GetDeltaTime());

		Input::UpdateKeyStates();// call this after all the inputs have been processed
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

void Application::CreatePlayer(glm::vec3 pos, int leftKey, int rightKey, int jumpKey) {

	ecs::Entity player = manager.createEntity();
	manager.addComponent(player, ecs::MeshRendererComponent());
	manager.addComponent(player, ecs::TransformComponent());
	manager.addComponent(player, ecs::KeyboardInputComponent());
	manager.addComponent(player, ecs::PlayerStateInfoComponent());
	manager.addComponent(player, ecs::RigidBodyComponent());
	manager.addComponent(player, ecs::ColliderComponent());
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(player);
	meshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sword")));
	meshRenderer.material = assetMan->GetMaterial("test");
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(player);
	transform.transform.SetPosition(pos);
	ecs::KeyboardInputComponent& keyboardInput = manager.getComponentStore<ecs::KeyboardInputComponent>().get(player);
	keyboardInput.map["Jump"] = jumpKey;
	keyboardInput.map["MoveLeft"] = leftKey;
	keyboardInput.map["MoveRight"] = rightKey;
	manager.registerEntity(player);
}
