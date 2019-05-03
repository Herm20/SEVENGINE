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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::Init(AssetManager * assetMan) {

	cubeMesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh("box")));

	u8 colliderColorRed[3] = { 255, 0, 0 };
	u8 colliderColorGreen[3] = { 0, 255, 0 };
	u8 colliderColorBlue[3] = { 0, 255, 255 };
	u8 colliderColorGray[3] = { 120, 120, 120 };
	colliderTextureRed = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorRed));
	colliderTextureGreen = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorGreen));
	colliderTextureBlue = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorBlue));
	colliderTextureGray = boost::shared_ptr<Texture>(new Texture(1, 1, 3, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, (const void*)colliderColorGray));

	assetMan->CreateMaterial("collider-red", colliderTextureRed, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("black"), assetMan->GetShaderProgram("rawcolor"));
	assetMan->CreateMaterial("collider-green", colliderTextureGreen, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("black"), assetMan->GetShaderProgram("rawcolor"));
	assetMan->CreateMaterial("collider-blue", colliderTextureBlue, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("black"), assetMan->GetShaderProgram("rawcolor"));
	assetMan->CreateMaterial("collider-gray", colliderTextureGray, assetMan->GetTexture("defaultNormal"), assetMan->GetTexture("black"), assetMan->GetShaderProgram("rawcolor"));
	colliderMatRed = assetMan->GetMaterial("collider-red");
	colliderMatGreen = assetMan->GetMaterial("collider-green");
	colliderMatBlue = assetMan->GetMaterial("collider-blue");
	colliderMatGray = assetMan->GetMaterial("collider-gray");

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

#include <iostream>
void Renderer::startFrame(float dt) {

	//Wipe the screen with that sweet sweet cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 0.0f);

	//Clear those buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Input::GetKeyDown(GLFW_KEY_GRAVE_ACCENT)) {
		renderColliders = !renderColliders;
	}

}

void Renderer::updateEntity(float dt, ecs::Entity entity) {

	// Model
	ecs::MeshRendererComponent& meshRenderer = manager.getComponentStore<ecs::MeshRendererComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);

	meshRenderer.mesh->Render(
		transform.transform,
		curCamera,
		meshRenderer.material,
		lights
	);
	// Collider
	if (renderColliders) {
		if (manager.getComponentStore<ecs::ColliderComponent>().has(entity)) {
			ecs::ColliderComponent& collider = manager.getComponentStore<ecs::ColliderComponent>().get(entity);
			boost::shared_ptr<Material> colliderMat = colliderMatGray;
			if (ecs::ColliderType::Hurtbox == collider.type) {
				colliderMat = collider.isColliding ? colliderMatRed : colliderMatGreen;
			} else if (ecs::ColliderType::Hitbox == collider.type) {
				colliderMat = colliderMatBlue;
			}
			cubeMesh->Render(
				collider.transform,
				curCamera,
				colliderMat,
				lights,
				true
			);
		}
	}

}

void Renderer::endFrame(float dt) {

	glBindVertexArray(0);

	//Swap front and back buffers
	glfwSwapBuffers(window);

}