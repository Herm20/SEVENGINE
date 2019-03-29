/*#include "InputManager.h"
#include <iostream>

//std::map<const char*, int> InputManager::FightKeyMap;
//std::map<const char*, int> InputManager::MenuKeyMap;
//std::map<const char*, int> InputManager::MenuMouseMap;
//
//std::vector<std::vector<const char*>> InputManager::ComboMovesList;
//std::vector<std::vector<const char*>> InputManager::PotentialMovesList;
//std::vector<std::map<const char*, int>> InputManager::MapArray1, InputManager::MapArray2;
//
//int InputManager::contextState;
//int InputManager::moveIndex;
//std::chrono::duration<float> InputManager::lastMoveTime;
InputManager* InputManager::instance;

InputManager::InputManager()
{
	timer = Timer::GetInstance();
	Init();
}

InputManager* InputManager::GetInstance() 
{
	if (!instance) 
	{
		instance = new InputManager();
	}
	return instance;
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

	ComboMovesList.push_back({"Combo1","FistAttack1","FistAttack1","FistAttack1","FistAttack1"});
	ComboMovesList.push_back({"Combo2","KickAttack1","KickAttack1","KickAttack2","KickAttack2"});
	ComboMovesList.push_back({"Combo3","FistAttack1","KickAttack1","FistAtttack2","KickAttack2" });
	ComboMovesList.push_back({"Combo4","KickAttack1","FistAttack1","FistAttack1","KickAttack1"});
}

void InputManager::ConfigureToDefaults() 
{
	MapArray1[0]["MoveLeft"]    = GLFW_KEY_A;
	MapArray1[0]["MoveRight"]   = GLFW_KEY_D;
	MapArray1[0]["Jump"]		= GLFW_KEY_SPACE;
	MapArray1[0]["FistAttack1"] = GLFW_KEY_LEFT_SHIFT;
	MapArray1[0]["FistAttack2"] = GLFW_KEY_V;
	MapArray1[0]["KickAttack1"] = GLFW_KEY_LEFT_CONTROL;
	MapArray1[0]["KickAttack2"] = GLFW_KEY_C;
}

void InputManager::ValidateKeyInput(int x)
{
	using namespace std;
	for (auto it = MapArray1[0].begin(); it!=MapArray1[0].end();it++) 
	{
		if(x==it->second)
		{
			cout << it->first << endl;
			if (moveIndex == 0) 
			{
				CheckForCombo(it->first, timer->GetCurrentTime());
			}
			else 
			{
				ContinueCombo(it->first, timer->GetCurrentTime());
			}
		}
	}
}

void InputManager::ValidateMouseInput(int x)
{
	using namespace std;
	for (auto it = MapArray1[2].begin(); it != MapArray1[2].end(); it++)
	{
		if (x == it->second)
		{
			cout << it->first << endl;
		}
	}
}

void InputManager::CheckForCombo(const char* x, std::chrono::duration<float> t)
{
	lastMoveTime = t;
	PotentialMovesList.clear();
	for (int i = 0; i<ComboMovesList.size();i++) 
	{
		if (x == ComboMovesList[i][1]) 
		{
			PotentialMovesList.push_back(ComboMovesList[i]);
		}
	}
	if (PotentialMovesList.size() > 0) 
	{
		moveIndex = 1;
	}
	
}

void InputManager::ContinueCombo(const char* x, std::chrono::duration<float> time)
{
	int t = 0;
	for (int i = 0; i < PotentialMovesList.size() + t; i++) 
	{
		if (x != PotentialMovesList[i-t][moveIndex+1]) 
		{
			PotentialMovesList.erase(PotentialMovesList.begin() + i - t);
			t++;
		}
	}
	
	if (PotentialMovesList.size()>0 && std::chrono::milliseconds(500) > std::chrono::duration_cast<std::chrono::milliseconds>(time - lastMoveTime))
	{
			
		if ((PotentialMovesList.size() == 1)&& (PotentialMovesList[0].size())-2==moveIndex) 
		{
			std::cout << "Combo Executed!!\n";
			moveIndex = 0;
			ExecuteCombo(PotentialMovesList[0][0]);// passes in the string at the 0th index of the combo move which is the name of the move itself
		}
		else 
		{
			moveIndex++;
		}
		lastMoveTime = time;
	}
	else 
	{
		std::cout << "Combo Failed!\n";
		moveIndex = 0;
		CheckForCombo(x, time);
	}
	
}

void InputManager::ExecuteCombo(const char* combo) // helper function to map the correct function for the correct combo;
{
	
}

InputManager::~InputManager() 
{
	delete instance;
}*/