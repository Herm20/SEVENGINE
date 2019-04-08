#include "Renderer.h"

#include "Components/MeshRendererComponent.h"
#include "Physics/ColliderComponent.h"

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
	
	boxMesh = boost::shared_ptr<Mesh>(new Mesh(am->GetMesh("box")));

	entities = new Entity[2];

	MeshRendererComponent* mr1 = entities[0].AddComponent<MeshRendererComponent>();
	mr1->mesh = boost::shared_ptr<Mesh>(new Mesh(am->GetMesh("box")));
	mr1->shaderProgram = am->GetShaderProgram("def");
	mr1->texture = am->GetTexture("test");

	MeshRendererComponent* mr2 = entities[1].AddComponent<MeshRendererComponent>();
	mr2->mesh = boost::shared_ptr<Mesh>(new Mesh(am->GetMesh("sword")));
	mr2->shaderProgram = am->GetShaderProgram("def");
	mr2->texture = am->GetTexture("test");
	entities[1].SetPosition(glm::vec3(3, 0, 0));
	entities[1].AddComponent<ColliderComponent>();

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
		if (meshRenderer) {
			meshRenderer->mesh->Render(
				entities[i].GetWorldPosition(),
				meshRenderer->shaderProgram,
				meshRenderer->texture
			);
		}

		ColliderComponent* coll = entities[i].GetComponent<ColliderComponent>();
		if (coll && meshRenderer) {
			boxMesh->Render(
				entities[i].GetWorldPosition(),
				meshRenderer->shaderProgram,
				meshRenderer->texture,
				true
			);
		}

	}
	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

	//Poll for and process events
	glfwPollEvents();
}