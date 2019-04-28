#ifndef COMBO_MANAGER_H_
#define COMBO_MANAGER_H_

#include "Timer.h"
#include <string>
#include <vector>
#include <map>

class ComboManager 
{
private:
	bool ContinueCombo(std::string);
	Timer* timer;

public:
	ComboManager(std::map<std::string,int>);
	~ComboManager();
	void CheckForCombo(int);
	void ChangeKeyMap(std::map<std::string, int>);
	
private:
	std::map<std::string, int> m_keyMap;
	std::vector<std::vector<std::string>> m_comboList;
	std::vector<std::vector<std::string>> possibleCombos;
	int comboCount;
	bool comboRunning;
	std::chrono::duration<float> lastMoveTime;
};

#endif // !COMBO_MANAGER_H_

