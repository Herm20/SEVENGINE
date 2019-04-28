#include "ComboManager.h"
#include <iostream>

ComboManager::ComboManager(std::map<std::string, int> keyMap) 
{
	m_comboList.push_back({"Jab","Hook","FrontKick","RoundKick"});
	m_comboList.push_back({"Jab","Jab","Hook","Hook"});
	m_comboList.push_back({"Hook","Hook","RoundKick","FrontKick"});
	m_comboList.push_back({"RoundKick","FrontKick","FrontKick","RoundKick"});

	comboCount = 0;
	m_keyMap = keyMap;
}

ComboManager::~ComboManager() 
{

}

void ComboManager::ChangeKeyMap(std::map<std::string, int> keyMap) 
{
	m_keyMap = keyMap;
}

void ComboManager::CheckForCombo(int keyValue)//default combofunction to be acessed by the application for checking or contining combos
{
	std::string move;

	for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++) 
	{
		if (it->second = keyValue) 
		{
			move = it->first;
		}
	}

	if (!ContinueCombo(move))
	{
		possibleCombos.clear();
		//pushes in all possible combos starting with this move if a comborun was not already in development
		for (int i = 0; i < m_comboList.size(); i++) 
		{
			if (move == m_comboList[i][0])
			{
				possibleCombos.push_back(m_comboList[i]);
			}
		}
		lastMoveTime = timer->GetCurrentTime();
	}
}

bool ComboManager::ContinueCombo(std::string move)
{
	std::chrono::duration<float> currentTime = Timer::GetCurrentTime();
	if(possibleCombos.size() == 0)return false;
	
	if (std::chrono::milliseconds(500) > std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime))
	{
		std::cout << "combo failed!\n";
		return false;
	}

	int t = 0;
	for (int i = 0; i < possibleCombos.size()+t; i++) 
	{
		if (move != possibleCombos[i-t][comboCount]) 
		{
			possibleCombos.erase(possibleCombos.begin() + i - t);
		}
	}

	if (possibleCombos.size() > 0) 
	{
		if ((possibleCombos.size() == 1)) 
		{
			if ((possibleCombos[0].size() - 1) == comboCount)
			{
				//EXECUTE COMBO
				std::cout << "COMBO SUCCESSFULL\n";
			}
		}
		return true;
	}
	else 
	{
		comboCount = 0;
		return false;
	}
}

