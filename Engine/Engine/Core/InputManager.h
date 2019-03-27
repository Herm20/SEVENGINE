//#ifndef INPUTMANAGER_H_
//#define INPUTMANAGER_H_
//
//#include <GLFW/glfw3.h>
////#include "Timer.h"
//#include <map>
//#include <Vector>
//
//class InputManager 
//{
//	//Timer* timer;
//	static InputManager* instance;
//	std::map<const char*, int> FightKeyMap; //key map for when we fight
//	std::map<const char*, int> MenuKeyMap; // key map for when we are in main menu
//	std::map<const char*, int> MenuMouseMap; // mousebutton map for when we are in Main menu
//	
//	std::vector<std::map<const char*, int>> MapArray1,MapArray2;// Vector for the above maps
//	std::vector<std::vector<const char*>> ComboMovesList;// vector for storing a list of moves for a particular combo preceeded by the name of the combo
//	std::vector<std::vector<const char*>> PotentialMovesList;
//	
//	//std::chrono::duration<float> lastMoveTime;
//	int moveIndex;
//	int contextState;// 2 for now(Menu(Main & Pause) and Fight)
//
//public:
//	static InputManager* GetInstance();
//
//	inline std::vector<std::map<const char*, int>>  GetKeyMapArray1() const { return MapArray1; }
//	inline std::vector<std::map<const char*, int>>  GetKeyMapArray2() const { return MapArray2; }
//	
//	void ValidateKeyInput(int);
//	void ValidateMouseInput(int);
//	void CheckForCombo(const char*, std::chrono::duration<float>);
//	void ContinueCombo(const char* x, std::chrono::duration<float> t);
//
//private:
//	InputManager();
//	void Init();
//	~InputManager();
//	void ExecuteCombo(const char*);
//	void ConfigureToDefaults();// sets all inputs to default keys
//	//bunch of static callbacks for calling relevant methods from the entity class wrapper/interface for input.
//};
//
//#endif // !INPUTMANAGER_H_
