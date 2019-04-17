#include "Renderer.h"

#include "Components/MeshRendererComponent.h"
#include "Physics/ColliderComponent.h"
#include "ECS/Manager.h"

#include <iostream>

Renderer::Renderer(ecs::Manager& manager) : ecs::System(manager)
{

	ecs::ComponentTypeSet requiredComponents;
	ecs::ComponentType mrcType = ecs::MeshRendererComponent::_mType;
	ecs::ComponentType tcType = ecs::TransformComponent::_mType;
	requiredComponents.insert(mrcType);
	requiredComponents.insert(tcType);

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
	//delete [] entities;
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

void Renderer::startFrame(float dt) {

	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::updateEntity(float dt, ecs::Entity entity) {
	
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);
	meshRenderer.mesh->Render(
		transform.position,
		meshRenderer.shaderProgram,
		meshRenderer.texture
	);

}

void Renderer::endFrame(float dt) {

	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

}
