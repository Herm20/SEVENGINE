#include "Camera.h"
#include "Timer.h"

Timer clock1;

Camera::Camera()
{
	location = { 0,1,2 };
	rotation = { 0,0,0 };
}


Camera::~Camera()
{
}

void Camera::update()
{
	velocity = { 0,0,0 };

	// Look at matrix
	mat3 rotMat = (mat3)yawPitchRoll(rotation.y, rotation.x, rotation.z);

	vec3 eye = location;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	mat4 lookAtMat = lookAt(eye, center, up);

	// Perspective matrix
	float zoom = 1.f;
	int width = 800;
	int height = 600;

	fieldOfView = 3.14159f * .4f / zoom;
	aspectRatio = (float)width / (float)height;
	nearDistance = .01f;
	farDistance = 1000.f;

	mat4 perspectiveMat = perspective(fieldOfView, aspectRatio, nearDistance, farDistance);

	// update to the world veiw matrix
	cameraMatrix = perspectiveMat * lookAtMat;

	glUniform3fv(5, 1, &location[0]);

	// upload the matrix
	glUniformMatrix4fv(4, 1, GL_FALSE, &cameraMatrix[0][0]);
}