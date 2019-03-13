#include "InputManager.h"

InputManager::InputManager()
{
	Init();
}

void InputManager::Init() 
{
	FightKeyMap["MoveLeft"] = GLFW_KEY_A;
	FightKeyMap["MoveRight"] = GLFW_KEY_D;
	FightKeyMap["Jump"] = GLFW_KEY_SPACE;
	FightKeyMap["FistAttack1"] = GLFW_KEY_LEFT_SHIFT;
	FightKeyMap["FistAttack2"] = GLFW_KEY_V;
	FightKeyMap["KickAttack1"] = GLFW_KEY_LEFT_CONTROL;
	FightKeyMap["KickAttack2"] = GLFW_KEY_C;
}

void InputManager::ConfigureToDefaults() 
{
	FightKeyMap["MoveLeft"] = GLFW_KEY_A;
	FightKeyMap["MoveRight"] = GLFW_KEY_D;
	FightKeyMap["Jump"] = GLFW_KEY_SPACE;
	FightKeyMap["FistAttack1"] = GLFW_KEY_LEFT_SHIFT;
	FightKeyMap["FistAttack2"] = GLFW_KEY_V;
	FightKeyMap["KickAttack1"] = GLFW_KEY_LEFT_CONTROL;
	FightKeyMap["KickAttack2"] = GLFW_KEY_C;
}
