#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <glm/glm.hpp>

#include "../Object.h"
#include "Collider.h"

using namespace glm;

class CollisionManager {

private:

	bool TestAxis(vec3 L, vec3 cA, vec3 cB, vec3 rA, vec3 rB);

	// Radial Projection Vectors
	vec3 GetRadialVectorOBB(const Collider& o, vec3 L);

	// Collision Tests
	bool CollidesOBBvOBB(const Collider& a, const Collider& b);

public:

};

#endif