#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include <glm/glm.hpp>

#include "../Object.h"
#include "ColliderComponent.h"

using namespace glm;

class CollisionManager {

private:

	bool TestAxis(vec3 L, vec3 cA, vec3 cB, vec3 rA, vec3 rB);

	// Radial Projection Vectors
	vec3 GetRadialVectorOBB(const ColliderComponent& o, vec3 L);

	// Collision Tests
	bool CollidesOBBvOBB(const ColliderComponent& a, const ColliderComponent& b);

public:

};

#endif