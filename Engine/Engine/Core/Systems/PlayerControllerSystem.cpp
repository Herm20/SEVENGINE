#include "PlayerControllerSystem.h"
#include "../ECS/Manager.h"

int PlayerControllerSystem::count = 0;

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

	defaultList[0] = { GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_G, GLFW_KEY_H, GLFW_KEY_B, GLFW_KEY_N, GLFW_KEY_LEFT_SHIFT };
	defaultList[1] = { GLFW_KEY_LEFT,GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_KP_5, GLFW_KEY_KP_6, GLFW_KEY_KP_2,GLFW_KEY_KP_3 };

	count = 0;

	CreateMaps();
	SetDefaults();
}


//////////////////////////////////Virtual Functions///////////////////////////////////////////////////////////
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

	/////////////////////////////////////Input Checks/////////////////////////////////////
	//make sure GetKeyDown is called before UpdateKeyStates in the update loop otherwise you will never get a true return value
	
	if (GetKey(keyMap["leftMove"])) 
	{
		if (GetKey(keyMap["powerKey"])) 
		{
			//Run to Left
		}
		else 
		{
			//move to Left	
		}
	}

	if (GetKey(keyMap["rightMove"]))
	{
		if (GetKey(keyMap["powerKey"]))
		{
			//Run to right
		}
		else
		{
			//move to right	
		}
	}

	if (GetKeyDown(keyMap["jump"]))//will need one more variable for checking if the player is free to perform this move or not
	{
		//jump
	}

	if (GetKey(keyMap["crouch"])) //will need one more variable for checking if the player is free to perform this move or not
	{
		//crouch
	}

	if (GetKeyDown(keyMap["jab"])) //will need one more variable for checking if the player is free to perform this move or not
	{
		if (GetKey(keyMap["powerKey"])) 
		{
			//perform delayed but powerful jab
		}
		else 
		{
			//perform simple jab
		}
	}

	if (GetKeyDown(keyMap["hook"]))//will need one more variable for checking if the player is free to perform this move or not 
	{
		if (GetKey(keyMap["powerKey"]))
		{
			//perform delayed but powerful hook
		}
		else
		{
			//perform simple hook
		}
	}

	if (GetKeyDown(keyMap["frontKick"]))//will need one more variable for checking if the player is free to perform this move or not s
	{
		if (GetKey(keyMap["powerKey"]))
		{
			//perform side kick
		}
		else
		{
			//perform simple front kick
		}
	}

	if (GetKeyDown(keyMap["roundKick"]))//will need one more variable for checking if the player is free to perform this move or not 
	{
		if (GetKey(keyMap["powerKey"]))
		{
			//perform round hook kick
		}
		else
		{
			//perform simple roundhouse
		}
	}


	///////////////////After all key checks
	//Updating the RecentKeyStates to their current statuses for use in the next frame
	UpdateKeyStates();
}

void PlayerControllerSystem::endFrame(float dt) {

}
///////////////////////////////////////////////////////////////////////////



///////////////////////////Input Functions/////////////////////////////
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

void PlayerControllerSystem::CreateMaps() 
{
	keyMap["leftMove"] = NULL;
	keyMap["rightMove"] = NULL;
	keyMap["jump"] = NULL;
	keyMap["crouch"] = NULL;
	keyMap["jab"] = NULL;
	keyMap["hook"] = NULL;
	keyMap["frontKick"] = NULL;
	keyMap["roundKick"] = NULL;
	keyMap["powerKey"] = NULL;
}

void PlayerControllerSystem::SetDefaults() 
{
	int counter = 0;
	for (auto it = keyMap.begin(); it != keyMap.end(); it++) 
	{
		it->second = defaultList[count - 1][counter];
		counter++;
	}
}