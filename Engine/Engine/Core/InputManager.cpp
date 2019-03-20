#include "InputManager.h"
#include <iostream>

std::map<const char*, int> InputManager::FightKeyMap;
std::map<const char*, int> InputManager::MenuKeyMap;
std::map<const char*, int> InputManager::MenuMouseMap;
std::vector<std::map<const char*, int>> InputManager::MapArray1, InputManager::MapArray2;
int InputManager::contextState;

InputManager::InputManager()
{
	Init();
}

void InputManager::Init() 
{
	FightKeyMap["MoveLeft"]	   = GLFW_KEY_A;
	FightKeyMap["MoveRight"]   = GLFW_KEY_D;
	FightKeyMap["Jump"]		   = GLFW_KEY_SPACE;
	FightKeyMap["FistAttack1"] = GLFW_KEY_LEFT_SHIFT;
	FightKeyMap["FistAttack2"] = GLFW_KEY_V;
	FightKeyMap["KickAttack1"] = GLFW_KEY_LEFT_CONTROL;
	FightKeyMap["KickAttack2"] = GLFW_KEY_C;

	MapArray1.push_back(FightKeyMap);

	MenuKeyMap["MoveDown"]   = GLFW_KEY_DOWN;
	MenuKeyMap["MoveUp"]	 = GLFW_KEY_UP;
	MenuKeyMap["SlideLeft"]  = GLFW_KEY_LEFT;
	MenuKeyMap["SlideRight"] = GLFW_KEY_RIGHT;
	MenuKeyMap["Access"]	 = GLFW_KEY_ENTER;

	MapArray1.push_back(MenuKeyMap);

	MenuMouseMap["LeftClick"]   = GLFW_MOUSE_BUTTON_LEFT;
	MenuMouseMap["RightClick"]  = GLFW_MOUSE_BUTTON_RIGHT;
	MenuMouseMap["MiddleClick"] = GLFW_MOUSE_BUTTON_MIDDLE;

	MapArray1.push_back(MenuMouseMap);
}

void InputManager::ConfigureToDefaults() 
{
	MapArray1[0]["MoveLeft"]    = GLFW_KEY_A;
	MapArray1[0]["MoveRight"]   = GLFW_KEY_D;
	MapArray1[0]["Jump"]		   = GLFW_KEY_SPACE;
	MapArray1[0]["FistAttack1"] = GLFW_KEY_LEFT_SHIFT;
	MapArray1[0]["FistAttack2"] = GLFW_KEY_V;
	MapArray1[0]["KickAttack1"] = GLFW_KEY_LEFT_CONTROL;
	MapArray1[0]["KickAttack2"] = GLFW_KEY_C;
}

void InputManager::ValidateKeyInput(int x)
{
	using namespace std;
	for (map<const char*, int>::iterator it = MapArray1[0].begin(); it!=MapArray1[0].end();it++) 
	{
		if(x==it->second)
		{
			cout << it->first << endl;
		}
	}
}

void InputManager::ValidateMouseInput(int x)
{
	using namespace std;
	for (map<const char*, int>::iterator it = MapArray1[2].begin(); it != MapArray1[2].end(); it++)
	{
		if (x == it->second)
		{
			cout << it->first << endl;
		}
	}
}