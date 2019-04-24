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

	void ReloadScripts();

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt , ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

	void SCRIPT_Entity_GetPosition();
	void SCRIPT_Entity_GetRotation();
	void SCRIPT_Entity_GetScale();
	void SCRIPT_Entity_SetPosition(glm::vec3 newPos);
	void SCRIPT_Entity_SetRotation(glm::quat newRot);
	void SCRIPT_Entity_SetScale(glm::vec3 newSca);
	void SCRIPT_Entity_ForwardVector();
	void SCRIPT_Entity_RightVector();
	void SCRIPT_Entity_UpVector();
	void SCRIPT_Entity_Translate(glm::vec3 vec);
	void SCRIPT_Entity_TranslateLocal(glm::vec3 vec);
	void SCRIPT_Entity_Rotate(glm::quat quat);
	void SCRIPT_Entity_RotateLocal(glm::quat quat);
	void SCRIPT_Entity_Scale(glm::vec3 vec);
	void SCRIPT_Entity_ScaleAdd(glm::vec3 vec);
};

#endif
