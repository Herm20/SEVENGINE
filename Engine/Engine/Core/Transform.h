#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"

using namespace glm;

class Transform
{
private:
	quat rot; // Rotation quaternion
	vec3 pos; // Position vector
	vec3 sca; // Scale vector
public:
	inline Transform() :
		rot(identity<quat>()),
		pos(0.0f),
		sca(1.0f)
	{
		// Nothing interesting to do here
	}
	inline Transform(const Transform& copy) :
		rot(copy.rot),
		pos(copy.pos),
		sca(copy.sca)
	{
		// Nothing interesting to do here
	}
	inline Transform(vec3 position, quat rotation = identity<quat>(), vec3 scale = vec3(1.0f)) :
		rot(rotation),
		pos(position),
		sca(scale)
	{
		// Nothing interesting to do here
	}
	inline ~Transform() {}

	inline Transform& operator= (const Transform& copy)
	{
		pos = copy.pos;
		rot = copy.rot;
		sca = copy.sca;

		return *this;
	}

	inline vec3 GetPosition() const { return pos; }
	inline quat GetRotation() const { return rot; }
	inline vec3 GetScale()    const { return sca; }

	inline void SetPosition(vec3 position) { pos = position; }
	inline void SetRotation(quat rotation) { rot = rotation; }
	inline void SetRotation(float angle, vec3 axis) {
		SetRotation(glm::angleAxis(angle, axis));
	}
	inline void SetRotation(float yaw, float pitch, float roll) {
		SetRotation(glm::toQuat(glm::yawPitchRoll(yaw, pitch, roll)));
	}
	inline void SetScale(vec3 scale)       { sca = scale; }

	inline vec3 ForwardVector() const { return rotate(rot, vec3(0.0f, 0.0f, 1.0f)); }
	inline vec3 RightVector()   const { return rotate(rot, vec3(1.0f, 0.0f, 0.0f)); }
	inline vec3 UpVector()      const { return rotate(rot, vec3(0.0f, 1.0f, 0.0f)); }

	inline mat4 GetMatrix() const { return scale(translate(identity<mat4>(), pos) * toMat4(rot), sca); }
	inline mat3 GetInverseTransposeMatrix() const { return mat3(transpose(inverse((scale(translate(identity<mat4>(), pos) * toMat4(rot), sca))))); }

	// Translate with respect to self
	inline void TranslateLocal(vec3 v) { pos += rotate(rot, v); }
	// Translate with respect to world
	inline void TranslateGlobal(vec3 v) { pos += v; }
	// Rotate with respect to self
	inline void RotateLocal(quat q) { rot = normalize(cross(rot, q)); }
	// Rotate with respect to world
	inline void RotateGlobal(quat q) { rot = normalize(cross(q, rot)); }
	// Add vector to scale
	inline void ScaleAdd(vec3 v) { sca += v; }
	// Multiply scale by vector factor
	inline void ScaleMul(vec3 v) { sca *= v; }
};

#endif
