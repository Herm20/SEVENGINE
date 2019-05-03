#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../ECS/System.h"
#include "InputPoller.h"

class CameraSystem
{
public:
	CameraSystem(ecs::Manager& manager); // Setting required components
	~CameraSystem();
	void Init(GLFWwindow* window); // Setting default values
	void Update(int winWidth, int winHeight); // Updates camera matrixes and passes them to the renderer
	void Movement(GLFWwindow* winPtr, int winWidth, int winHeight); // Changes values to allow camera to move besides on matrixes

	Input inputPoller; // For camera Input

	glm::mat4x4 cameraMatrix;
	glm::vec3 rotation, position, velocity;

	// Helper Functions
	glm::mat4x4 GetCameraMatrix();
	glm::vec3 GetRotation();
	glm::vec3 GetPosition();
	glm::vec3 GetVelocity();

	inline void SetPosition(glm::vec3 newpos) { position = newpos; }
	inline void SetRotation(glm::vec3 newrot) { rotation = newrot; }
	inline void SetVelocity(glm::vec3 newvel) { velocity = newvel; }

private:
	// Variable for view matrix
	float fieldOfView;
	float aspectRatio;
	float nearDistance;
	float farDistance;
};
#endif // CAMERASYSTEM_H_

