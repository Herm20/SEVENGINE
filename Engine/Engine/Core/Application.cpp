#include "Application.h"

#include "ECS/System.h"

#include <boost/chrono/chrono.hpp>
#include <boost/thread/thread.hpp>

Timer Application::Time;

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
	camera = new Camera();

	inputPoller.Init(renderer->GetWindow());

	assetMan->SetAssetDir("Assets");
	assetMan->LoadAssetsFromAssetDir();

	masterBG = new AudioManager();
	masterBG->InitSoundBG();
	masterBG->LoadBGFile("Assets/Audio/Background/gameMusic.mp3");
	masterBG->Play();
	masterBG->SetVolume(0.02f);

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

	// Systems will run in the order they are added
	manager.addSystem(ecs::System::Ptr(new PlayerControllerSystem(manager)));
	manager.addSystem(ecs::System::Ptr(new RigidBodySystem(manager)));
	manager.addSystem(ecs::System::Ptr(renderer));

	// Dummy Player Entity
	player1 = manager.createEntity();
	manager.addComponent(player1, ecs::MeshRendererComponent());
	manager.addComponent(player1, ecs::TransformComponent());
	manager.addComponent(player1, ecs::KeyboardInputComponent());
	manager.addComponent(player1, ecs::PlayerStateInfoComponent());
	manager.addComponent(player1, ecs::RigidBodyComponent());
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(player1);
	meshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sword")));
	meshRenderer.shaderProgram = assetMan->GetShaderProgram("def");
	meshRenderer.texture = assetMan->GetTexture("test");
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(player1);
	transform.transform.SetPosition(glm::vec3(0, 0, 0));
	manager.registerEntity(player1);
	ecs::KeyboardInputComponent& keyboardInput = manager.getComponentStore<ecs::KeyboardInputComponent>().get(player1);
	keyboardInput.map["Jump"] = GLFW_KEY_UP;
	keyboardInput.map["MoveLeft"] = GLFW_KEY_LEFT;
	keyboardInput.map["MoveRight"] = GLFW_KEY_RIGHT;

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
		Time.update();
		CamMovement();
		camera->update();

		manager.updateEntities(Time.dt);

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
	delete assetMan;
}

/// SUPER TEMP

void Application::CamMovement()
{
	// FPS Controls
	int w = renderer->GetWindowWidth();
	int h = renderer->GetWindowHeight();
	float sens = .001;
	double x = 0;
	double y = 0;

	glfwGetCursorPos(renderer->GetWindow(), &x, &y);

	camera->rotation.y -= sens * (x - w * .5f);
	camera->rotation.x -= sens * -(y - h * .5f);
	camera->rotation.x = glm::clamp(camera->rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

	glfwSetCursorPos(renderer->GetWindow(), w * .5f, h * .5f);

	// move with W,A,S,D
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camera->rotation.y, camera->rotation.x, camera->rotation.z);

	if (Input::GetKey(GLFW_KEY_A))
		camera->velocity += R * glm::vec3(1, 0, 0);

	if (Input::GetKey(GLFW_KEY_D))
		camera->velocity += R * glm::vec3(-1, 0, 0);

	if (Input::GetKey(GLFW_KEY_W))
		camera->velocity += R * glm::vec3(0, 0, 1);

	if (Input::GetKey(GLFW_KEY_S))
		camera->velocity += R * glm::vec3(0, 0, -1);

	if (Input::GetKey(GLFW_KEY_SPACE))
		camera->velocity += R * glm::vec3(0, 1, 0);

	if (Input::GetKey(GLFW_KEY_X))
		camera->velocity += R * glm::vec3(0, -1, 0);

	float speed = 10.0f;
	if (camera->velocity != glm::vec3())
	{
		camera->velocity = glm::normalize(camera->velocity) * speed * Time.dt;
	}

	camera->location += camera->velocity * speed * Time.dt;
	camera->velocity = { 0,0,0 };
}
/// SUPER TEMP