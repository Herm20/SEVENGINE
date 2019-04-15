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

	ecs::PlayerStateInfoComponent& playerState = manager.getComponentStore<ecs::PlayerStateInfoComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);
	
	playerState.wiggleTest += dt;
	transform.position.x = sin(playerState.wiggleTest);

	// Get input component
	// Check if button is pressed
		// If so, do thing

}

void PlayerControllerSystem::endFrame(float dt) {

}