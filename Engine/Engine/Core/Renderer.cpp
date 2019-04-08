#include "Renderer.h"

#include "Components/MeshRendererComponent.h"

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
		entities[i].Destroy();
	}

	delete [] entities;
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
	/*meshes = new Mesh[5];
	meshes[0] = Mesh(am->GetMesh("box"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(0.0f, 0.0f, 5.0f));
	meshes[1] = Mesh(am->GetMesh("sphere"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(5.0f, 0.0f, 0.0f));
	meshes[2] = Mesh(am->GetMesh("sword"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(0.0f, 5.0f, 0.0f));
	meshes[3] = Mesh(am->GetMesh("teapot"), am->GetShaderProgram("def"), am->GetTexture("test"), glm::vec3(-5.0f, 0.0f, 0.0f));*/
	entities = new Entity[2];

	MeshRendererComponent* mr1 = new MeshRendererComponent();
	mr1->mesh = boost::shared_ptr<Mesh>(new Mesh(am->GetMesh("box")));
	mr1->shaderProgram = am->GetShaderProgram("def");
	mr1->texture = am->GetTexture("test");
	entities[0].AddComponent<MeshRendererComponent>(mr1);

	MeshRendererComponent* mr2 = new MeshRendererComponent();
	mr2->mesh = boost::shared_ptr<Mesh>(new Mesh(am->GetMesh("sword")));
	mr2->shaderProgram = am->GetShaderProgram("def");
	mr2->texture = am->GetTexture("test");
	entities[1].SetPosition(glm::vec3(3, 0, 0));
	entities[1].AddComponent<MeshRendererComponent>(mr2);

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

	for (int i = 0; i < 2; i++)
	{
		// Draw object
		MeshRendererComponent* meshRenderer = entities[i].GetComponent<MeshRendererComponent>();
		if (!meshRenderer) continue;
		meshRenderer->mesh->Render(
			entities[i].GetWorldPosition(), 
			meshRenderer->shaderProgram, 
			meshRenderer->texture);
	}
	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}