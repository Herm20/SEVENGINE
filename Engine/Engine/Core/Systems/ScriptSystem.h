#ifndef SCRIPT_SYSTEM_H_
#define SCRIPT_SYSTEM_H_

#include "../Types.h"
#include "../ECS/System.h"
#include "../ECS/Component.h"

#include <glm/glm.hpp>

class lua_State;

class ScriptSystem : public ecs::System
{
private:
	lua_State* state;
	u64 nextID;
	ecs::Entity currentEntity;

	void LoadScript(ecs::ScriptComponent& script);

public:
	ScriptSystem(ecs::Manager& manager);
	~ScriptSystem();

	void Init();
	void Destroy();

	void Run();
	void Reload();

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt , ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

	void SetEntityPosition(glm::vec3 newPos);
};

#endif
