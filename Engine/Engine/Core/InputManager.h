#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <GLFW/glfw3.h>
#include <map>
#include <Vector>

class InputManager 
{
	static std::map<const char*, int> FightKeyMap; //key map for when we fight
	static std::map<const char*, int> MenuKeyMap; // key map for when we are in main menu
	static std::map<const char*, int> MenuMouseMap; // mousebutton map for when we are in Main menu
	
	static std::vector<std::map<const char*, int>> MapArray1,MapArray2;// Vector for the above maps
	
	static int contextState;// 2 for now(Menu(Main & Pause) and Fight)

public:
	InputManager();
	inline std::vector<std::map<const char*, int>>  GetKeyMapArray1() const { return MapArray1; }
	inline std::vector<std::map<const char*, int>>  GetKeyMapArray2() const { return MapArray2; }
	static void ValidateKeyInput(int);
	static void ValidateMouseInput(int);

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