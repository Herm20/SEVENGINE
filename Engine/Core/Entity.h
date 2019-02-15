#ifndef ENTITY_H_
#define ENTITY_H_

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include <vector>
#include <string>

#include "Types.h"
#include "Transform.h"

class Entity
{
private:
	std::vector<Entity*> children;
	Entity* parent;

	std::vector<std::string> tags;

	// TODO : Component and scene stuff goes here

	// Cached data for speeding up repeated access operations
	mat4 world;
	mat4 invWorld;
	quat worldRotation;

	// Transform defining transformation relative to parent
	Transform local;

	// Control variables for determining when to recalculate world or inverse matrix
	bool needsUpdated;
	bool needsInverseUpdated;
	bool needsRotationUpdated;

	// Helper methods
	void AddChild(Entity* newChild);
	void RemoveChild(Entity* child);
	void RequireUpdate();

public:
	Entity();
	Entity(const Transform& t = Transform(), Entity* parentEntity = nullptr);
	~Entity();

	// Destroy the entity and its children - if you want support for a time-to-destroy parameter, ping me and I'll implement it script-side (because scripts are the only place something like that would conceivably be needed and it saves implementation bloat here)
	void Destroy();

	// Changes the parent Entity to another or none (nullptr)
	void SetParent(Entity* newParent, bool keepWorldTransform);
	// Will probably implement more functionality for handling parent-child relations (likely only script-side)
	inline Entity* GetParent() const { return parent; }
	inline std::vector<Entity*> GetChildren() const { return children; }
	inline u64 GetChildCount() const { return children.size(); }

	// Will probably move tag system purely into script-side once that's up-and-running
	void AddTag(std::string tag);
	void RemoveTag(std::string tag);

	// TODO : Component and scene stuff goes here

	inline Transform GetTransform() const { return local; }
	inline vec3      GetPosition() const  { return local.GetPosition(); }
	inline quat      GetRotation() const  { return local.GetRotation(); }
	inline vec3      GetScale() const     { return local.GetScale(); }

	// Not const because these can regenerate cached data under the hood
	vec3 GetWorldPosition();
	quat GetWorldRotation();

	// Ditto
	mat4 GetWorldMatrix();
	mat4 GetInverseMatrix();

	// Set position with respect to parent
	void SetPosition(vec3 position);
	// Set position with respect to self
	void SetPositionLocal(vec3 position);
	// Set position with respect to world
	void SetPositionWorld(vec3 position);
	// Set position with respect to another entity
	inline void SetPositionEntity(Entity& e, vec3 position) { SetPositionWorld(vec3(e.GetWorldMatrix() * vec4(position, 1.0f))); }
	// Set rotation with respect to parent
	void SetRotation(quat rotation);
	// Set rotation with respect to world
	void SetRotationWorld(quat rotation);
	// Set rotation with respect to another entity
	inline void SetRotationEntity(Entity& e, quat rotation) { SetRotationWorld(cross(e.GetWorldRotation(), rotation)); }
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
	// Rotate around another entity, preserving original orientation
	void OrbitAboutEntity(Entity* e, quat q);

	// Rotate about point offset via self, preserving original orientation
	void OrbitAboutPoint(vec3 v, quat q);
	// Rotate about point offset from parent, preserving original orientation
	void OrbitAboutPointParent(vec3 v, quat q);
	// Rotate about point offset from world, preserving original orientation
	void OrbitAboutPointWorld(vec3 v, quat q);
	// Rotate about point offset from another entity, preserving original orientation
	void OrbitAboutPointEntity(Entity* e, vec3 v, quat q);

	// Rotate around parent (both rotation and translation)
	void RevolveAboutParent(quat q);
	// Rotate around world (both rotation and translation)
	void RevolveAboutWorld(quat q);
	// Rotate around another entity (both rotation and translation)
	void RevolveAboutEntity(Entity* e, quat q);
	
	// Rotate about point offset via self (both rotation and translation)
	void RevolveAboutPoint(vec3 v, quat q);
	// Rotate about point offset from parent (both rotation and translation)
	void RevolveAboutPointParent(vec3 v, quat q);
	// Rotate about point offset from world (both rotation and translation)
	void RevolveAboutPointWorld(vec3 v, quat q);
	// Rotate about point offset from another entity (both rotation and translation)
	void RevolveAboutPointEntity(Entity* e, vec3 v, quat q);
};

#endif