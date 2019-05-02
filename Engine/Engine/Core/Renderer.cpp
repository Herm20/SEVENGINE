#include "Renderer.h"

#include "ECS/Manager.h"

Renderer::Renderer(ecs::Manager& manager) : ecs::System(manager)
{
	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::MeshRendererComponent::_mType);
	requiredComponents.insert(ecs::TransformComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));

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

	//SkyBox
	sky = 0;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::Init(AssetManager * assetMan) {

	cubeMesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("box")));

	sky = new SkyBox(assetMan);

	u8 colliderColorRed[3] = { 255, 0, 0 };
	u8 colliderColorGreen[3] = { 0, 255, 0 };
	colliderTextureRed = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorRed));
	colliderTextureGreen = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorGreen));

	assetMan->CreateMaterial("collider-red", colliderTextureRed, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	assetMan->CreateMaterial("collider-green", colliderTextureGreen, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("defaultSpecular"), assetMan->GetShaderProgram("def"));
	colliderMatRed = assetMan->GetMaterial("collider-red");
	colliderMatGreen = assetMan->GetMaterial("collider-green");

}

Renderer::~Renderer()
{
	delete sky;
	sky = 0;

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

#include <iostream>
void Renderer::startFrame(float dt) {

	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::updateEntity(float dt, ecs::Entity entity) {

	// Model
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);

	sky->Render(curCamera);

	meshRenderer.mesh->Render(
		transform.transform,
		curCamera,
		meshRenderer.material,
		lights
	);

	// Collider
	if (manager.getComponentStore<ecs::ColliderComponent>().has(entity)) {
		ecs::ColliderComponent& collider = manager.getComponentStore<ecs::ColliderComponent>().get(entity);
		boost::shared_ptr<Material> colliderMat = collider.isColliding ? colliderMatRed : colliderMatGreen;
		cubeMesh->Render(
			transform.transform,
			curCamera,
			colliderMat,
			lights,
			true
		);
	}

}

void Renderer::endFrame(float dt) {

	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

}