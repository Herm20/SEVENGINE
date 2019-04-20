#include "RigidBodySystem.h"

#include "../ECS/Manager.h"

RigidBodySystem::RigidBodySystem(ecs::Manager& manager) : ecs::System(manager) {

	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::TransformComponent::_mType);
	requiredComponents.insert(ecs::RigidBodyComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));

}

void RigidBodySystem::startFrame(float dt) {
}

void RigidBodySystem::updateEntity(float dt, ecs::Entity entity) {

	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);
	ecs::RigidBodyComponent& rigidBody = manager.getComponentStore<ecs::RigidBodyComponent>().get(entity);
	transform.transform.SetPosition(transform.transform.GetPosition() + rigidBody.velocity * dt);

}

void RigidBodySystem::endFrame(float dt) {
}