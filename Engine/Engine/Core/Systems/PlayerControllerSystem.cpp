#include "PlayerControllerSystem.h"

#include "../ECS/Manager.h"

PlayerControllerSystem::PlayerControllerSystem(ecs::Manager& manager) : ecs::System(manager) {

	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::TransformComponent::_mType);
	requiredComponents.insert(ecs::KeyboardInputComponent::_mType);
	requiredComponents.insert(ecs::PlayerStateInfoComponent::_mType);
	requiredComponents.insert(ecs::RigidBodyComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));

}

void PlayerControllerSystem::startFrame(float dt) {


}

void PlayerControllerSystem::updateEntity(float dt, ecs::Entity entity) {

	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);
	transform.position.x += 1.0f * dt;

	// Get input component
	// Check if button is pressed
		// If so, do thing

}

void PlayerControllerSystem::endFrame(float dt) {

}