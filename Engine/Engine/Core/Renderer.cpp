#include "Renderer.h"

Renderer::Renderer()
{
	//Initialize the GLFW Library
	if (!glfwInit())
	{
		return;
	}

	//Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, "SEVENGINE", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	//Make the window's context current
	glfwMakeContextCurrent(window);

	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}


Renderer::~Renderer()
{
	for(u32 i = 0; i < 5; i++)
	{
		meshes[i].Destroy();
	}

	delete [] meshes;
	glfwTerminate();
}

//Returns the active window
GLFWwindow * Renderer::GetWindow()
{
	return window;
}

int Renderer::GetWindowHeight()
{
	return height;
}

int Renderer::GetWindowWidth()
{
	return width;
}

void Renderer::CreateMeshes()
{
	meshes = new Mesh[5];
	meshes[0] = Mesh(am->GetMesh("box"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(0.0f, 0.0f, 5.0f));
	meshes[1] = Mesh(am->GetMesh("sphere"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(5.0f, 0.0f, 0.0f));
	meshes[2] = Mesh(am->GetMesh("sword"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(0.0f, 5.0f, 0.0f));
	meshes[3] = Mesh(am->GetMesh("teapot"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(-5.0f, 0.0f, 0.0f));
}

void Renderer::SetAssetManager(const AssetManager* am)
{
	this->am = am;
}

//Iterates through and draws all entities to the screen
void Renderer::Draw()
{
	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 4; i++)
	{
		// Draw object
		meshes[i].Render();
	}
	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}