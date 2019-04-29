#include "CollisionSystem.h"

#include "../ECS/Manager.h"
#include "../Timer.h"

using namespace glm;

inline vec3 e(const ecs::ColliderComponent& coll) { return coll.size; }
inline vec3 c(const ecs::ColliderComponent& coll) { return coll.position; }
inline mat3 u(const ecs::ColliderComponent& coll) { return coll.rotation; };

bool TestAxis(vec3 L, vec3 cA, vec3 cB, vec3 rA, vec3 rB) {
	return abs(dot(L, (cA - cB))) > abs(dot(L, rA)) + abs(dot(L, rB));
}

// Radial Projection Vectors
vec3 GetRadialVectorOBB(const ecs::ColliderComponent& coll, vec3 L) {
	return u(coll) * (sign(L * u(coll)) * e(coll));
}

bool CollidesOBBvOBB(const ecs::ColliderComponent& a, const ecs::ColliderComponent& b) {

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

CollisionSystem::CollisionSystem(ecs::Manager& manager, ScriptSystem* scriptSys) : ecs::System(manager) {

	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::TransformComponent::_mType);
	requiredComponents.insert(ecs::ColliderComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));

	scriptSystem = scriptSys;

}

void CollisionSystem::startFrame(float dt) {
}

#include <iostream>
void CollisionSystem::updateEntity(float dt, ecs::Entity entity) {

	const std::unordered_map<ecs::Entity, ecs::ColliderComponent> allColliders = manager.getComponentStore<ecs::ColliderComponent>().getComponents();

	ecs::ColliderComponent& collider = manager.getComponentStore<ecs::ColliderComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);

	collider.position = transform.transform.GetPosition();
	collider.rotation = toMat3(transform.transform.GetRotation());
	collider.active = true;
	collider.isColliding = false;

	for (auto it = allColliders.begin(); it != allColliders.end(); it++) {
		
		ecs::Entity otherEntity = it->first;
		if (otherEntity != entity) {

			ecs::ColliderComponent otherCollider = it->second;
			if (!otherCollider.active) return;
			bool colliding = CollidesOBBvOBB(collider, otherCollider);

			// If first frame of collision
			if (colliding && !collider.collisions[otherEntity] && ecs::ColliderType::Hurtbox == collider.type) {
				scriptSystem->SendMessage(entity, 3, "oncollision", "01");
			}
			collider.collisions[otherEntity] = colliding;

			if (colliding) collider.isColliding = true;

		}

	}

}

void CollisionSystem::endFrame(float dt) {
}