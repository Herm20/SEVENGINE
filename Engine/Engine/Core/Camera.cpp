#include "Camera.h"

using namespace std;
using namespace glm;

Camera::Camera()
{
	position = { 0,0,5 };
	rotation = { 0,0,0 };
	velocity = { 0,0,0 };
}


Camera::~Camera()
{
}

void Camera::update()
{
	// Look at matrix
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

	glm::vec3 eye = position;
	glm::vec3 center = eye + rotMat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat * glm::vec3(0, 1, 0);

	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);

	// Perspective matrix
	float zoom = 1.f;
	int width = 800;
	int height = 600;

	fieldOfView = 3.14159f * .4f / zoom;
	aspectRatio = (float)width / (float)height;
	nearDistance = .01f;
	farDistance = 1000.f;

	glm::mat4 perspectiveMat = glm::perspective(fieldOfView, aspectRatio, nearDistance, farDistance);

	// update to the world veiw matrix
	cameraMatrix = perspectiveMat * lookAtMat;
}

void Camera::movement(GLFWwindow* winPtr, int winHeight, int winWidth)
{
	// FPS Controls
	float sens = .005;
	int w = winWidth;
	int h = winHeight;
	double x;
	double y;

	glfwGetCursorPos(winPtr, &x, &y);

	rotation.y -= sens * (x - w * .5f);
	rotation.x -= sens * (y - h * .5f);
	rotation.x = glm::clamp(rotation.x, (-.5f * glm::pi<float>()), (.5f * glm::pi<float>()));

	glfwSetCursorPos(winPtr, w * .5f, h * .5f);
}
