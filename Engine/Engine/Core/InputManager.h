#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <GLFW/glfw3.h>
#include <map>

class InputManager 
{
	std::map<const char*, int> FightKeyMap; //key map for when we fight
	std::map<const char*, int> MenuKeyMap; // key map for when we are in main menu
	std::map<const char*, int> PauseKeyMap; // keymap for when we are in pause menu
	std::map<const char*, int> PauseMouseMap; // mousebutton map for when we are in pause menu
	std::map<const char*, int> MenuMouseMap; // mousebutton map for when we are in Main menu

	int contextState;// 3 for now(Main Menu, pause Menu and Fight)

public:
	InputManager();

private:
	void Init();
	void ConfigureToDefaults();// sets all inputs to default keys

	//bunch of static callbacks for calling relevant methods from the entity class wrapper/interface for input.
};

#endif // !INPUTMANAGER_H_

//Movement
//Jump
//FistAttack1
//FistAttack2
//KickAttack1
//KickAttack2