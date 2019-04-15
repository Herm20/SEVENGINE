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
	ecs::RigidBodyComponent& rigidbody = manager.getComponentStore<ecs::RigidBodyComponent>().get(entity);
	
	playerState.wiggleRate += dt;
	transform.position.x = sin(playerState.wiggleRate);

	// Jump every now and then
	playerState.jumpTimer += dt;
	if (playerState.jumpTimer >= playerState.jumpRate && !playerState.isJumping) {
		playerState.jumpTimer = 0;
		rigidbody.velocity.y = 3;
		playerState.isJumping = true;
	}

	// Gravity
	if (playerState.isJumping) {
		rigidbody.velocity.y -= 5.0f * dt;
	}

	// Stop jumping when we hit the ground
	if (transform.position.y < 0) {
		transform.position.y = 0;
		playerState.isJumping = false;
		rigidbody.velocity.y = 0;
	}

}

void PlayerControllerSystem::endFrame(float dt) {

}