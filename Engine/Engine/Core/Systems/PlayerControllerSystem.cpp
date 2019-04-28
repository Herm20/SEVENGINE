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
	ecs::KeyboardInputComponent& inputMap = manager.getComponentStore<ecs::KeyboardInputComponent>().get(entity);

	glm::vec3 pos = transform.transform.GetPosition();

	bool left = Input::GetKey(inputMap.map["MoveLeft"]);
	bool right = Input::GetKey(inputMap.map["MoveRight"]);
	glm::vec3 moveDir(0, 0, 0);
	if (left && !right) {
		moveDir = glm::vec3(-1, 0, 0);
	}
	else if (right && !left) {
		moveDir = glm::vec3(1, 0, 0);
	}
	pos += moveDir * playerState.moveSpeed * dt;

	if (Input::GetKey(inputMap.map["Jump"]) && !playerState.isJumping) {
		rigidbody.velocity.y = 3;
		playerState.isJumping = true;
	}

	// Gravity
	if (playerState.isJumping) {
		rigidbody.velocity.y -= 5.0f * dt;
	}

	// Stop jumping when we hit the ground
	if (pos.y < 0) {
		pos.y = 0;
		playerState.isJumping = false;
		rigidbody.velocity.y = 0;
	}
	transform.transform.SetPosition(pos);
}

void PlayerControllerSystem::endFrame(float dt) {

}