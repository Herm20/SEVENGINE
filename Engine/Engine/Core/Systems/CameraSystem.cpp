#include "CameraSystem.h"

#include "../ECS/Component.h"
#include "../ECS/Manager.h"

CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}

void CameraSystem::Update()
{
}

void CameraSystem::Movement()
{
}

glm::mat4x4 CameraSystem::GetCameraMatrix()
{
	return glm::mat4x4();
}

glm::vec3 CameraSystem::GetRotation()
{
	return glm::vec3();
}

glm::vec3 CameraSystem::GetPosition()
{
	return glm::vec3();
}

glm::vec3 CameraSystem::GetVelocity()
{
	return glm::vec3();
}
