#ifndef PLAYER_CONTROLLER_SYSTEM_H
#define PLAYER_CONTROLLER_SYSTEM_H

#include "InputPoller.h"
#include "../ECS/System.h"
#include <map>
#include <vector>

class PlayerControllerSystem : public ecs::System {

private:
	bool recentKeyStates[Max_keys];
	static int count;
	std::map<const char*, int> keyMap;
	std::vector<std::vector<int>> defaultList;
	std::vector<int> assignedKeys;

public:

	explicit PlayerControllerSystem(ecs::Manager& manager);

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;
	void UpdateKeyStates();
	bool GetKey(int);
	bool GetKeyDown(int);
	void SetDefaults();
	void CreateMaps();
};

#endif

