#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "../Component.h"

#include <glm/glm.hpp>

using namespace glm;

class Collider : Component {

private:

	vec3 size;

public:

	vec3 GetScale() const;
	vec3 GetPosition() const;
	quat GetRotation() const;

};

#endif