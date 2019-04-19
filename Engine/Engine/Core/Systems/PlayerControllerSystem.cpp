#include "PlayerControllerSystem.h"

#include "../ECS/Manager.h"

PlayerControllerSystem::PlayerControllerSystem(ecs::Manager& manager) : ecs::System(manager) {

	ecs::ComponentTypeSet requiredComponents;
	requiredComponents.insert(ecs::TransformComponent::_mType);
	requiredComponents.insert(ecs::KeyboardInputComponent::_mType);
	requiredComponents.insert(ecs::PlayerStateInfoComponent::_mType);
	requiredComponents.insert(ecs::RigidBodyComponent::_mType);
	setRequiredComponents(std::move(requiredComponents));

	////////////Input Stuff///////////////////////////////////////
	for (int i = 0; i < Max_keys; i++)
	{
		recentKeyStates[i] = Input::ReturnStatus(i);
	}
}

void PlayerControllerSystem::startFrame(float dt) {

}

void PlayerControllerSystem::updateEntity(float dt, ecs::Entity entity) {

	ecs::PlayerStateInfoComponent& playerState = manager.getComponentStore<ecs::PlayerStateInfoComponent>().get(entity);
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(entity);
	ecs::RigidBodyComponent& rigidbody = manager.getComponentStore<ecs::RigidBodyComponent>().get(entity);
	
	playerState.wiggleRate += dt;
	glm::vec3 holder = transform.transform.GetPosition();
	holder.x = sin(playerState.wiggleRate);

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
	if (holder.y < 0) {
		holder.y = 0;
		playerState.isJumping = false;
		rigidbody.velocity.y = 0;
	}
	transform.transform.SetPosition(holder);
	/////////////////////////////////////Input STUFF/////////////////////////////////////

	//make sure GetKeyDown is called before UpdateKeyStates in the update loop otherwise you will never get a true return value
	if (GetKeyDown(GLFW_KEY_A) )
	{
		//do something if A is pressed down
	}

	if (GetKey(GLFW_KEY_A)) 
	{
		//do something if A's state is pressed
	}


	//Updating the RecentKeyStates to their current statuses for use in the next frame
	UpdateKeyStates();
}

void PlayerControllerSystem::endFrame(float dt) {

}

//////Input Functions
void PlayerControllerSystem::UpdateKeyStates() 
{
	for (int i = 0; i < Max_keys; i++)
	{
		recentKeyStates[i] = Input::ReturnStatus(i);
	}
}

bool PlayerControllerSystem::GetKey(int keyValue) 
{
	return Input::ReturnStatus(keyValue);
}

bool PlayerControllerSystem::GetKeyDown(int keyValue)
{
	bool keyPressed = false;
	bool curretState = Input::ReturnStatus(keyValue);
	if(!recentKeyStates[keyValue]) 
	{
		if (recentKeyStates[keyValue] != curretState) 
		{
			keyPressed = true;
		}
	}
	//recentKeyStates[keyValue] = curretState;
	return keyPressed;
}