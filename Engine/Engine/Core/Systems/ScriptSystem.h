#ifndef SCRIPT_SYSTEM_H_
#define SCRIPT_SYSTEM_H_

#include "../Types.h"
#include "../ECS/System.h"
#include "Camera.h"
#include "../ECS/Component.h"

#include <boost/container/string.hpp>
#include <glm/glm.hpp>

class lua_State;
class AssetManager;

class ScriptSystem : public ecs::System
{
private:
	lua_State* state;
	AssetManager* assetMan;
	u64 nextID;

	void LoadScript(ecs::Entity entity, ecs::ScriptComponent& script);

public:
	ecs::Entity currentEntity;
	CameraSystem* cam;

	ScriptSystem(ecs::Manager& manager, AssetManager* assetManager, CameraSystem* cams);
	~ScriptSystem();

	void Init();
	void Destroy();

	// Hot-reload all active scripts
	void ReloadScripts();

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt , ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

	// Send a message to a script from outside the scripting system
	void SendMessage(ecs::Entity entity, u64 script_id, const boost::container::string& message, const boost::container::string& data);

	void SCRIPT_World_SpawnEntity();
	void SCRIPT_World_DestroyEntity(ecs::Entity entity);

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
