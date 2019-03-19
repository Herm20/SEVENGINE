#include "CollisionManager.h"

inline vec3 e(const Object& o) { return o.GetScale(); }
inline vec3 c(const Object& o) { return o.GetPosition(); }
inline mat3 u(const Object& o) { return (mat3)o.GetRotation(); };

bool CollisionManager::TestAxis(vec3 L, vec3 cA, vec3 cB, vec3 rA, vec3 rB) {
	return abs( dot(L, (cA - cB)) ) > abs( dot(L, rA) ) + abs( dot(L, rB) );
}

// Radial Projection Vectors
vec3 CollisionManager::GetRadialVectorOBB(const Object& o, vec3 L) {
	return u(o) * ( sign(L * u(o)) * e(o) );
}

bool CollisionManager::CollidesOBBvOBB(const Object& a, const Object& b) {

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