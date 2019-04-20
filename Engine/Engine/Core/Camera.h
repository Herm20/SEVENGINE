#ifndef CAMERA_H_
#define CAMERA_H_
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <map>

class Camera
{
public:
	glm::mat4x4 cameraMatrix;
	glm::vec3 rotation, position, velocity;
	Camera();
	~Camera();
	void update();
	void movement(GLFWwindow* winPtr, int winHeight, int winWidth);

private:
	float fieldOfView;
	float aspectRatio;
	float nearDistance;
	float farDistance;
};
#endif // CAMERA_H

