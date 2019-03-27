#include "Application.h"

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
	
	assetMan = new AssetManager();
	camera = new Camera();
	renderer = new Renderer(assetMan);
	assetMan->LoadDirectory("Assets");
	Load();

	//TODO: Change this to dynamically create programs
	renderer->CreateBasicProgram();
	//masterBG.InitSound();
	//masterBG.LoadFile("audio/gameMusic.mp3");
	//masterBG.Play(false);

	/// SUPER TEMP
	//Set the click function when loading game
	glfwSetKeyCallback(renderer->GetWindow(), keyCallback);
	// Set the keypress function when loading game
	glfwSetMouseButtonCallback(renderer->GetWindow(), mouseClick);
	///

	printf("INIT\n");
}

void Application::Load()
{
	boost::shared_ptr<MeshData> data = assetMan->GetMesh("Mario");
}

void Application::Run()
{
	// Making it "true" for now
	while (!glfwWindowShouldClose(renderer->GetWindow()) && !inputIsDown[GLFW_KEY_ESCAPE])
	{
		Time.update();
		camera->movement(renderer->GetWindow(), renderer->GetWindowHeight(), renderer->GetWindowWidth());
		//camera->update();
		CamMovement();

		printf("Time: %f", Time.fps);
		system("CLS");

		// Update objects, process input, draw objects to the screen, et cetera
		boost::this_thread::sleep_for(boost::chrono::milliseconds(250));
		renderer->Draw();
	}
}

void Application::Exit()
{
	delete assetMan;
	delete renderer;
	printf("END\n");
}

/// SUPER TEMP
void Application::CamMovement()
{
	// FPS Controls
	float sens = .005;
	int w = renderer->GetWindowWidth();
	int h = renderer->GetWindowHeight();
	double x;
	double y;

	glfwGetCursorPos(renderer->GetWindow(), &x, &y);

	camera->rotation.y -= sens * (x - w * .5f);
	camera->rotation.x -= sens * (y - h * .5f);
	camera->rotation.x = glm::clamp(camera->rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

	glfwSetCursorPos(renderer->GetWindow(), w * .5f, h * .5f);

	// move with W,A,S,D
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camera->rotation.y, camera->rotation.x, camera->rotation.z);

	if (inputIsDown[GLFW_KEY_A])
	{
		camera->velocity += R * glm::vec3(-1, 0, 0);
	}

	if (inputIsDown[GLFW_KEY_D])
	{
		camera->velocity += R * glm::vec3(1, 0, 0);
	}

	if (inputIsDown[GLFW_KEY_W])
	{
		camera->velocity += R * glm::vec3(0, 0, -1);
	}

	if (inputIsDown[GLFW_KEY_S])
	{
		camera->velocity += R * glm::vec3(0, 0, 1);
	}

	float speed = 1.f;
	if (camera->velocity != glm::vec3())
	{
		camera->velocity = glm::normalize(camera->velocity) * speed;
	}

	camera->location += camera->velocity * Time.dt;
}
/// SUPER TEMP

