#include "Application.h"

#include "ECS/System.h"

#include <boost/chrono/chrono.hpp>
#include <boost/thread/thread.hpp>

Timer Application::Time;

//const ecs::ComponentType ecs::MeshRendererComponent::_mType = 1;

namespace
{
	// The click function can't be a method
	map<int, bool> inputIsDown;
	map<int, bool> inputWasDown;

	void mouseClick(GLFWwindow * GLFWindowPtr2, int button, int action
		, int mobs) {

		inputIsDown[button] = action;
	}

	void keyCallback(GLFWwindow * window, int key, int scancode, int action
		, int mods)
	{
		inputIsDown[key] = action;
	}
}

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
	glfwSetKeyCallback(renderer->GetWindow(), keyCallback);
	// Set the keypress function when loading game
	glfwSetMouseButtonCallback(renderer->GetWindow(), mouseClick);
	///

	manager.createComponentStore<ecs::MeshRendererComponent>();
	manager.createComponentStore<ecs::TransformComponent>();

	manager.addSystem(ecs::System::Ptr(renderer));

	e1 = manager.createEntity();
	manager.addComponent(e1, ecs::MeshRendererComponent());
	manager.addComponent(e1, ecs::TransformComponent());
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(e1);
	meshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sword")));
	meshRenderer.shaderProgram = assetMan->GetShaderProgram("def");
	meshRenderer.texture = assetMan->GetTexture("test");
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(e1);
	transform.position = glm::vec3(0, 0, 0);
	manager.registerEntity(e1);

	e2 = manager.createEntity();
	manager.addComponent(e2, ecs::MeshRendererComponent());
	manager.addComponent(e2, ecs::TransformComponent());
	ecs::MeshRendererComponent& meshRenderer2 = manager.getComponentStore<ecs::MeshRendererComponent>().get(e2);
	meshRenderer2.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("box")));
	meshRenderer2.shaderProgram = assetMan->GetShaderProgram("def");
	meshRenderer2.texture = assetMan->GetTexture("test");
	ecs::TransformComponent& transform2 = manager.getComponentStore<ecs::TransformComponent>().get(e2);
	transform2.position = glm::vec3(2, 0, 0);
	manager.registerEntity(e2);

	d1 = new Dummy(1);
	d2 = new Dummy(2);
	d3 = new Dummy(3);

	// Register all 
	EventSystem::Instance()->RegisterClient("Dummy Callback", d1);
	EventSystem::Instance()->RegisterClient("Dummy Callback", d2);
	EventSystem::Instance()->RegisterClient("Dummy Callback", d3);

	// Register Individual
	EventSystem::Instance()->RegisterClient("Callback 1", d1);
	EventSystem::Instance()->RegisterClient("Callback 2", d2);
	EventSystem::Instance()->RegisterClient("Callback 3", d3);
}

void Application::Load()
{
}

void Application::Run()
{
	while (!glfwWindowShouldClose(renderer->GetWindow()) && !inputIsDown[GLFW_KEY_ESCAPE])
	{
		Time.update();
		CamMovement();
		camera->update();

		manager.updateEntities(Time.dt);

		/// Testing Events
		if (inputIsDown[GLFW_KEY_G])
		{
			EventSystem::Instance()->SendEvent("Dummy Callback", (void*)1);
		}
			

		if (inputIsDown[GLFW_KEY_H])
		{
			EventSystem::Instance()->SendEvent("Callback 1", (void*)2);
		}
			

		if (inputIsDown[GLFW_KEY_J])
		{
			EventSystem::Instance()->SendEvent("Callback 2", (void*)3);
		}
			

		if (inputIsDown[GLFW_KEY_K])
		{
			EventSystem::Instance()->SendEvent("Callback 3", (void*)4);
		}

		if (inputIsDown[GLFW_KEY_L])
		{
			system("CLS");
		}
		EventSystem::Instance()->ProcessEvents();
		///

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
	delete d1;
	delete d2;
	delete d3;
}

/// SUPER TEMP

void Application::InitKeyCallbacks() {

}

void Application::CamMovement()
{
	// FPS Controls
	int w = renderer->GetWindowWidth();
	int h = renderer->GetWindowHeight();
	float sens = .001;
	double x = 0;
	double y = 0;

	//glfwGetCursorPos(renderer->GetWindow(), &x, &y);

	camera->rotation.y -= sens * (x - w * .5f);
	camera->rotation.x -= sens * -(y - h * .5f);
	camera->rotation.x = glm::clamp(camera->rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

	//glfwSetCursorPos(renderer->GetWindow(), w * .5f, h * .5f);

	// move with W,A,S,D
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camera->rotation.y, camera->rotation.x, camera->rotation.z);

	if (inputIsDown[GLFW_KEY_A])
		camera->velocity += R * glm::vec3(1, 0, 0);

	if (inputIsDown[GLFW_KEY_D])
		camera->velocity += R * glm::vec3(-1, 0, 0);

	if (inputIsDown[GLFW_KEY_W])
		camera->velocity += R * glm::vec3(0, 0, 1);

	if (inputIsDown[GLFW_KEY_S])
		camera->velocity += R * glm::vec3(0, 0, -1);

	if (inputIsDown[GLFW_KEY_SPACE])
		camera->velocity += R * glm::vec3(0, 1, 0);

	if (inputIsDown[GLFW_KEY_X])
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