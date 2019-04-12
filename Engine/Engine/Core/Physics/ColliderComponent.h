#ifndef COLLIDER_COMPONENT_H_
#define COLLIDER_COMPONENT_H_

#include "../ECS/Component.h"

#include <glm/glm.hpp>

using namespace glm;
using namespace ecs;

struct ColliderComponent : Component {
	vec3 size;
	vec3 position;
	mat3 rotation;
};

#endif