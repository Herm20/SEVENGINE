#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>

struct Light
{
	glm::vec3 pos; //! The position of the light
	float radius; //! The radius of the light
	glm::vec3 color; //! The color of the light
	float intensity; //! The intensity of the light
};

#endif
