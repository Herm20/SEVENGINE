#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "../Component.h"

#include <glm/glm.hpp>

using namespace glm;

struct Collider : Component {
	vec3 size;
	vec3 position;
	mat3 rotation;
};

#endif