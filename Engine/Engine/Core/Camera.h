#pragma once
#include "Object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

using namespace glm;

class Camera :
	public Object
{
public:
	mat4x4 cameraMatrix;

	float fieldOfView;
	float aspectRatio;
	float nearDistance;
	float farDistance;

	vec3 rotation, location, velocity;
	Camera();
	~Camera();
	void update();
};

