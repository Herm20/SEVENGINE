#include "Camera.h"

#include "../ECS/Component.h"
#include "../ECS/Manager.h"

CameraSystem::CameraSystem(ecs::Manager& manager)
{

}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::Init(GLFWwindow* window)
{
	position = { 0,1,5 };
	rotation = { 0,0,0 };
	velocity = { 0,0,0 };
	inputPoller.Init(window);
}

void CameraSystem::Update(int winWidth, int winHeight)
{
	// Look at matrix
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

	glm::vec3 eye = position;
	glm::vec3 center = eye + rotMat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat * glm::vec3(0, 1, 0);

	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);

	// Perspective matrix
	float zoom = 1.f;

	fieldOfView = 3.14159f * .4f / zoom;
	aspectRatio = (float)winWidth / (float)winHeight;
	nearDistance = .01f;
	farDistance = 1000.f;

	glm::mat4 perspectiveMat = glm::perspective(fieldOfView, aspectRatio, nearDistance, farDistance);

	// update to the world veiw matrix
	cameraMatrix = perspectiveMat * lookAtMat;
}

void CameraSystem::Movement(GLFWwindow* window, int winWidth, int winHeight)
{
	// FPS Controls
	int w = winWidth;
	int h = winHeight;
	float sens = .001;
	double x = 0;
	double y = 0;

	if (Input::GetMouse(GLFW_MOUSE_BUTTON_LEFT))
	{
		glfwGetCursorPos(window, &x, &y);

		rotation.y -= sens * (x - w * .5f);
		rotation.x -= sens * (y - h * .5f);
		rotation.x = glm::clamp(rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

		glfwSetCursorPos(window, w * .5f, h * .5f);
	}

	// move with W,A,S,D
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

	if (Input::GetKey(GLFW_KEY_A))
		velocity += R * glm::vec3(-1, 0, 0);

	if (Input::GetKey(GLFW_KEY_D))
		velocity += R * glm::vec3(1, 0, 0);

	if (Input::GetKey(GLFW_KEY_W))
		velocity += R * glm::vec3(0, 0, -1);

	if (Input::GetKey(GLFW_KEY_S))
		velocity += R * glm::vec3(0, 0, 1);

	if (Input::GetKey(GLFW_KEY_SPACE))
		velocity += R * glm::vec3(0, 1, 0);

	if (Input::GetKey(GLFW_KEY_X))
		velocity += R * glm::vec3(0, -1, 0);

	float speed = 10.0f;
	if (velocity != glm::vec3())
	{
		velocity = glm::normalize(velocity) * speed;
	}

	position += velocity * Timer::GetDeltaTime();
	velocity = { 0,0,0 };
}

glm::mat4x4 CameraSystem::GetCameraMatrix()
{
	return cameraMatrix;
}

glm::vec3 CameraSystem::GetRotation()
{
	return rotation;
}

glm::vec3 CameraSystem::GetPosition()
{
	return position;
}

glm::vec3 CameraSystem::GetVelocity()
{
	return velocity;
}
