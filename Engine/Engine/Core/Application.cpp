#include "Application.h"

#include "ECS/System.h"

#include <boost/chrono/chrono.hpp>
#include <boost/thread/thread.hpp>

Timer Application::Time;

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
	renderer->SetAssetManager(assetMan);
	renderer->CreateMeshes();
	//masterBG.InitSound();
	//masterBG.LoadFile("audio/gameMusic.mp3");
	//masterBG.Play(false);

	/// SUPER TEMP
	//Set the click function when loading game
	glfwSetKeyCallback(renderer->GetWindow(), keyCallback);
	// Set the keypress function when loading game
	glfwSetMouseButtonCallback(renderer->GetWindow(), mouseClick);
	///

	manager.createComponentStore<ecs::MeshRendererComponent>();

	manager.addSystem(ecs::System::Ptr(renderer));

	testEntity = manager.createEntity();
	manager.addComponent(testEntity, ecs::MeshRendererComponent());
	manager.registerEntity(testEntity);
	ecs::MeshRendererComponent testMeshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(testEntity);
	testMeshRenderer.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("sword")));
	testMeshRenderer.shaderProgram = assetMan->GetShaderProgram("def");
	testMeshRenderer.texture = assetMan->GetTexture("test");

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
		renderer->Draw();
	}
}

void Application::Exit()
{
	assetMan->SaveAssets();
	Logger::Log(Logger::LogType::MSG, "Exiting engine");
	std::string name = Logger::GetFormatedSystemTime();
	name += "-log.txt";
	assetMan->SaveAssetToFile("Log", name.c_str(), Logger::GetLog());
	delete assetMan;
	delete renderer;
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