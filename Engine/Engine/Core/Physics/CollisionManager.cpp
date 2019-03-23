#include "CollisionManager.h"

inline vec3 e(const Collider& coll) { return coll.GetScale(); }
inline vec3 c(const Collider& coll) { return coll.GetPosition(); }
inline mat3 u(const Collider& coll) { return (mat3)coll.GetRotation(); };

bool CollisionManager::TestAxis(vec3 L, vec3 cA, vec3 cB, vec3 rA, vec3 rB) {
	return abs( dot(L, (cA - cB)) ) > abs( dot(L, rA) ) + abs( dot(L, rB) );
}

// Radial Projection Vectors
vec3 CollisionManager::GetRadialVectorOBB(const Collider& coll, vec3 L) {
	return u(coll) * ( sign(L * u(coll)) * e(coll) );
}

bool CollisionManager::CollidesOBBvOBB(const Collider& a, const Collider& b) {

	vec3 cA = c(a);
	vec3 cB = c(b);
	vec3 L, rA, rB;

	// Check normal axes
	mat3 uA = u(a);
	mat3 uB = u(b);
	for (int i = 0; i < 3; i++) {

		L = uA[i];
		rA = GetRadialVectorOBB(a, L);
		rB = GetRadialVectorOBB(b, L);
		if (TestAxis(L, cA, cB, rA, rB)) return false;

		L = uB[i];
		rA = GetRadialVectorOBB(a, L);
		rB = GetRadialVectorOBB(b, L);
		if (TestAxis(L, cA, cB, rA, rB)) return false;

	}

	// Check all other axes
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			L = cross(uA[i], uB[i]);
			rA = GetRadialVectorOBB(a, L);
			rB = GetRadialVectorOBB(b, L);
			if (TestAxis(L, cA, cB, rA, rB)) return false;

		}
	}

	return true;

}