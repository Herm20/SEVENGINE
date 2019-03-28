#ifndef OBJECT_H_
#define OBJECT_H_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <boost/container/string.hpp>
#include <boost/container/vector.hpp>

#include "Types.h"
#include "Transform.h"

// Base class for Entities and any other objects that would make use of parent-child transformational relationships (e.g. bones for model animation)
class Object
{
private:
	// Cached data for speeding up repeated access operations
	mat4 world;
	mat4 invWorld;
	quat worldRotation;
#ifdef CORE_OBJECT_NO_DYNAMIC_UPDATE
	vec3 worldPosition;
#endif

	// Transform defining transformation relative to parent
	Transform local;

	// Control variables for determining when to recalculate world or inverse matrix
#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
	bool needsUpdated;
	bool needsInverseUpdated;
	bool needsRotationUpdated;
#endif

#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
	void RequireUpdate();
#else
// Effectively disabled
#define RequireUpdate() 
#endif

	// TODO : Why is C++ bad about this ; find something more clever to do
	friend class Entity;

protected:
	boost::container::vector<Object*> children;
	Object* parent;

	void AddChild(Object* newChild);
	void RemoveChild(Object* child);

public:
	Object();
	Object(const Transform& t, Object* parentObject = nullptr);
	virtual ~Object();

	// Changes the parent Object to another or none (nullptr)
	void SetParent(Object* newParent, bool keepWorldTransform);
	// Will probably implement more functionality for handling parent-child relations (likely only script-side)
	inline Object* GetParent() const { return parent; }
	inline boost::container::vector<Object*> GetChildren() const { return children; }
	inline u64 GetChildCount() const { return children.size(); }

	inline Transform GetTransform() const { return local; }
	inline vec3      GetPosition() const  { return local.GetPosition(); }
	inline quat      GetRotation() const  { return local.GetRotation(); }
	inline vec3      GetScale() const     { return local.GetScale(); }

	inline vec3 GetLocalForward() const { return local.ForwardVector(); }
	inline vec3 GetLocalRight() const   { return local.RightVector(); }
	inline vec3 GetLocalUp() const      { return local.UpVector(); }

	inline vec3 GetWorldForward() { return rotate(GetWorldRotation(), vec3(0.0f, 0.0f, 1.0f)); }
	inline vec3 GetWorldRight()   { return rotate(GetWorldRotation(), vec3(1.0f, 0.0f, 0.0f)); }
	inline vec3 GetWorldUp()      { return rotate(GetWorldRotation(), vec3(0.0f, 1.0f, 0.0f)); }
	
#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
	// Not const because these can regenerate cached data under the hood
	vec3 GetWorldPosition();
	quat GetWorldRotation();

	// Ditto
	mat4 GetWorldMatrix();
	mat4 GetInverseMatrix();
#else
	inline vec3 GetWorldPosition() const { return worldPosition; }
	inline quat GetWorldRotation() const { return worldRotation; }
	inline mat4 GetWorldMatrix() const { return world; }
	inline mat4 GetInverseMatrix() const { return invWorld; }

	void UpdateTransformationsRoot();
	void UpdateTransformationsChild();
#endif

	// Set position with respect to parent
	void SetPosition(vec3 position);
	// Set position with respect to self
	void SetPositionLocal(vec3 position);
	// Set position with respect to world
	void SetPositionWorld(vec3 position);
	// Set position with respect to another object
	inline void SetPositionObject(Object* o, vec3 position) { SetPositionWorld(vec3(o->GetWorldMatrix() * vec4(position, 1.0f))); }
	// Set rotation with respect to parent
	void SetRotation(quat rotation);
	// Set rotation with respect to world
	void SetRotationWorld(quat rotation);
	// Set rotation with respect to another object
	inline void SetRotationObject(Object* o, quat rotation) { SetRotationWorld(cross(o->GetWorldRotation(), rotation)); }
	// Set scale
	void SetScale(vec3 scale);

	// Translate with respect to parent
	void Translate(vec3 v);
	// Translate with respect to self
	void TranslateLocal(vec3 v);
	// Translate with respect to world
	void TranslateWorld(vec3 v);
	// Rotate with respect to parent
	void Rotate(quat q);
	// Rotate with respect to self
	void RotateLocal(quat q);
	// Rotate with respect to world
	void RotateWorld(quat q);
	// Scale
	void Scale(vec3 v);
	// Add to scale
	void ScaleAdd(vec3 v);

	// Rotate around parent, preserving original orientation
	void OrbitAboutParent(quat q);
	// Rotate around world, preserving original orientation
	void OrbitAboutWorld(quat q);
	// Rotate around another object, preserving original orientation
	void OrbitAboutObject(Object* o, quat q);

	// Rotate about point offset via self, preserving original orientation
	void OrbitAboutPoint(vec3 v, quat q);
	// Rotate about point offset from parent, preserving original orientation
	void OrbitAboutPointParent(vec3 v, quat q);
	// Rotate about point offset from world, preserving original orientation
	void OrbitAboutPointWorld(vec3 v, quat q);
	// Rotate about point offset from another object, preserving original orientation
	void OrbitAboutPointObject(Object* o, vec3 v, quat q);

	// Rotate around parent (both rotation and translation)
	void RevolveAboutParent(quat q);
	// Rotate around world (both rotation and translation)
	void RevolveAboutWorld(quat q);
	// Rotate around another object (both rotation and translation)
	void RevolveAboutObject(Object* o, quat q);
	
	// Rotate about point offset via self (both rotation and translation)
	void RevolveAboutPoint(vec3 v, quat q);
	// Rotate about point offset from parent (both rotation and translation)
	void RevolveAboutPointParent(vec3 v, quat q);
	// Rotate about point offset from world (both rotation and translation)
	void RevolveAboutPointWorld(vec3 v, quat q);
	// Rotate about point offset from another object (both rotation and translation)
	void RevolveAboutPointObject(Object* o, vec3 v, quat q);
};

#endif
