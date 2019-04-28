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

	renderer->Init(assetMan);

	eventMan = new EventManager();
	camera = new Camera();
	lightSystem = new LightSystem(manager);
	lightSystem->SetLightsVector(&renderer->GetLightVector());

	renderer->SetCurrentCamera(camera);

	inputPoller.Init(renderer->GetWindow());

	masterBG = new AudioManager();
	masterBG->InitSoundBG();
	masterBG->LoadBGFile("Assets/Audio/Background/gameMusic.mp3");
	//masterBG->Play();
	masterBG->SetVolume(0.08f);

	masterEffect = new AudioManager();
	masterEffect->InitSoundEffect();

	/// SUPER TEMP
	//Set the click function when loading game
	//glfwSetKeyCallback(renderer->GetWindow(), keyCallback);
	// Set the keypress function when loading game
	//glfwSetMouseButtonCallback(renderer->GetWindow(), mouseClick);
	///

	manager.createComponentStore<ecs::MeshRendererComponent>();
	manager.createComponentStore<ecs::TransformComponent>();
	manager.createComponentStore<ecs::KeyboardInputComponent>();
	manager.createComponentStore<ecs::PlayerStateInfoComponent>();
	manager.createComponentStore<ecs::RigidBodyComponent>();
	manager.createComponentStore<ecs::ColliderComponent>();
	manager.createComponentStore<ecs::LightComponent>();

	// Systems will run in the order they are added
	manager.addSystem(ecs::System::Ptr(new PlayerControllerSystem(manager)));
	manager.addSystem(ecs::System::Ptr(new RigidBodySystem(manager)));
	manager.addSystem(ecs::System::Ptr(new CollisionSystem(manager)));
	manager.addSystem(ecs::System::Ptr(lightSystem));
	manager.addSystem(ecs::System::Ptr(renderer));

	// Players
	CreatePlayer(glm::vec3(2, 0, 0), GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP);
	CreatePlayer(glm::vec3(-2, 0, 0), GLFW_KEY_J, GLFW_KEY_L, GLFW_KEY_I);

	ecs::Entity collidable = manager.createEntity();
	manager.addComponent(collidable, ecs::MeshRendererComponent());
	manager.addComponent(collidable, ecs::TransformComponent());
	manager.addComponent(collidable, ecs::ColliderComponent());
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(collidable);
	meshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sphere")));
	meshRenderer.material = assetMan->GetMaterial("test");
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(collidable);
	transform.transform.SetPosition(glm::vec3(0, 2.2, 0));
	transform.transform.SetRotation(glm::vec3(0, 0, 1), glm::pi<float>() / 4.f);
	manager.registerEntity(collidable);

	ecs::Entity e2 = manager.createEntity();
	manager.addComponent(e2, ecs::TransformComponent());
	manager.getComponentStore<ecs::TransformComponent>().get(e2).transform.SetRotation(glm::angleAxis(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	manager.addComponent(e2, ecs::LightComponent());
	//ecs::LightComponent & light = manager.getComponentStore<ecs::LightComponent>().get(player1);
	//light.light.color = (glm::vec3(0, 5, -1));
	manager.registerEntity(e2);

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
		CamMovement();
		camera->update();
		EventManager::ExecuteNext();

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

/// SUPER TEMP
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

void Application::CamMovement()
{
	// FPS Controls
	int w = renderer->GetWindowWidth();
	int h = renderer->GetWindowHeight();
	float sens = .001;
	double x = 0;
	double y = 0;

	if (Input::GetMouse(GLFW_MOUSE_BUTTON_LEFT))
	{
		glfwGetCursorPos(renderer->GetWindow(), &x, &y);

		camera->rotation.y -= sens * (x - w * .5f);
		camera->rotation.x -= sens * (y - h * .5f);
		camera->rotation.x = glm::clamp(camera->rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

		glfwSetCursorPos(renderer->GetWindow(), w * .5f, h * .5f);
	}

	// move with W,A,S,D
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camera->rotation.y, camera->rotation.x, camera->rotation.z);

	if (Input::GetKey(GLFW_KEY_A))
		camera->velocity += R * glm::vec3(-1, 0, 0);

	if (Input::GetKey(GLFW_KEY_D))
		camera->velocity += R * glm::vec3(1, 0, 0);

	if (Input::GetKey(GLFW_KEY_W))
		camera->velocity += R * glm::vec3(0, 0, -1);

	if (Input::GetKey(GLFW_KEY_S))
		camera->velocity += R * glm::vec3(0, 0, 1);

	if (Input::GetKey(GLFW_KEY_SPACE))
		camera->velocity += R * glm::vec3(0, 1, 0);

	if (Input::GetKey(GLFW_KEY_X))
		camera->velocity += R * glm::vec3(0, -1, 0);

	float speed = 10.0f;
	if (camera->velocity != glm::vec3())
	{
		camera->velocity = glm::normalize(camera->velocity) * speed;
	}

	camera->position += camera->velocity * Timer::GetDeltaTime();
	camera->velocity = { 0,0,0 };
}
/// SUPER TEMP
