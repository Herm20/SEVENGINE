#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <map>

class CameraSystem
{
public:
	CameraSystem();
	~CameraSystem();
	static void Update();
	static void Movement();
	glm::mat4x4 GetCameraMatrix();
	glm::vec3 GetRotation();
	glm::vec3 GetPosition();
	glm::vec3 GetVelocity();

private:
	float fieldOfView;
	float aspectRatio;
	float nearDistance;
	float farDistance;
	glm::mat4x4 cameraMatrix;
	glm::vec3 rotation, position, velocity;
};
#endif // CAMERASYSTEM_H_

