#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>

struct Light
{
	glm::vec3 pos = glm::vec3(0.0f); //! The position of the light
	float radius = 1.0f; //! The radius of the light
	glm::vec3 color = glm::vec3(1.0f); //! The color of the light
	float intensity = 1.0f; //! The intensity of the light
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 1.0f); //! The light direction
};

#endif
