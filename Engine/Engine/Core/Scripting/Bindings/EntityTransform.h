#ifndef BINDINGS_ENTITY_TRANSFORM_H_
#define BINDINGS_ENTITY_TRANSFORM_H_

#include "../BindingBase.h"
#include "../Utilities.h"

#include <glm/glm.hpp>
#include <cstdio>

extern "C" {
	int SCRIPT_Entity_GetPosition(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_GetPosition();
		return 1;
	}

	int SCRIPT_Entity_GetRotation(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_GetRotation();
		return 1;
	}

	int SCRIPT_Entity_GetScale(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_GetScale();
		return 1;
	}

	int SCRIPT_Entity_SetPosition(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_SetPosition(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Entity_SetRotation(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_SetRotation(SCRIPT_UTIL_GetQuaternion(state, 1));
		return 0;
	}

	int SCRIPT_Entity_SetScale(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_SetScale(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Entity_ForwardVector(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_ForwardVector();
		return 1;
	}

	int SCRIPT_Entity_RightVector(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_RightVector();
		return 1;
	}

	int SCRIPT_Entity_UpVector(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_UpVector();
		return 1;
	}

	int SCRIPT_Entity_Translate(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_Translate(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Entity_TranslateLocal(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_TranslateLocal(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Entity_Rotate(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_Rotate(SCRIPT_UTIL_GetQuaternion(state, 1));
		return 0;
	}

	int SCRIPT_Entity_RotateLocal(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_RotateLocal(SCRIPT_UTIL_GetQuaternion(state, 1));
		return 0;
	}

	int SCRIPT_Entity_Scale(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_Scale(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Entity_ScaleAdd(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Entity_ScaleAdd(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Animation_SetKey(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Animation_SetKey(SCRIPT_UTIL_GetString(state, 1));
		return 0;
	}

	int SCRIPT_Audio_PlayEffect(lua_State* state)
	{
		SCRIPT_system->SCRIPT_Audio_PlayEffect(SCRIPT_UTIL_GetCharString(state, 1));
		return 0;
	}
}

void ScriptSystem::SCRIPT_Entity_GetPosition()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushVector(state, transform.transform.GetPosition());
}

void ScriptSystem::SCRIPT_Entity_GetRotation()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushQuaternion(state, transform.transform.GetRotation());
}

void ScriptSystem::SCRIPT_Entity_GetScale()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushVector(state, transform.transform.GetScale());
}

void ScriptSystem::SCRIPT_Entity_SetPosition(glm::vec3 newPos)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.SetPosition(newPos);
}

void ScriptSystem::SCRIPT_Entity_SetRotation(glm::quat newRot)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.SetRotation(newRot);
}

void ScriptSystem::SCRIPT_Entity_SetScale(glm::vec3 newSca)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.SetScale(newSca);
}

void ScriptSystem::SCRIPT_Entity_ForwardVector()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushVector(state, transform.transform.ForwardVector());
}

void ScriptSystem::SCRIPT_Entity_RightVector()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushVector(state, transform.transform.RightVector());
}

void ScriptSystem::SCRIPT_Entity_UpVector()
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	SCRIPT_UTIL_PushVector(state, transform.transform.UpVector());
}

void ScriptSystem::SCRIPT_Entity_Translate(glm::vec3 vec)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.TranslateGlobal(vec);
}

void ScriptSystem::SCRIPT_Entity_TranslateLocal(glm::vec3 vec)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.TranslateLocal(vec);
}

void ScriptSystem::SCRIPT_Entity_Rotate(glm::quat quat)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.RotateGlobal(quat);
}

void ScriptSystem::SCRIPT_Entity_RotateLocal(glm::quat quat)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.RotateLocal(quat);
}

void ScriptSystem::SCRIPT_Entity_Scale(glm::vec3 vec)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.ScaleMul(vec);
}

void ScriptSystem::SCRIPT_Entity_ScaleAdd(glm::vec3 vec)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.ScaleAdd(vec);
}

void ScriptSystem::SCRIPT_Animation_SetKey(boost::container::string key)
{
	ecs::SpriteSheetComponent& ss = manager.getComponentStore<ecs::SpriteSheetComponent>().get(currentEntity);
	ss.currentAnimationId = key;
}

void ScriptSystem::SCRIPT_Audio_PlayEffect(const char* file)
{
	AudioManager::LoadEffectFile(file);
	AudioManager::PlayEffect();
}

inline void SCRIPT_BIND_EntityTransform(lua_State* state)
{
	// Create the entity library table and put it on the stack
	lua_newtable(state);
	lua_setglobal(state, "entity");
	lua_getglobal(state, "entity");

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_Entity_GetPosition);
	lua_setfield(state, -2, "getposition");
	lua_pushcfunction(state, SCRIPT_Entity_GetRotation);
	lua_setfield(state, -2, "getrotation");
	lua_pushcfunction(state, SCRIPT_Entity_GetScale);
	lua_setfield(state, -2, "getscale");
	lua_pushcfunction(state, SCRIPT_Entity_SetPosition);
	lua_setfield(state, -2, "setposition");
	lua_pushcfunction(state, SCRIPT_Entity_SetRotation);
	lua_setfield(state, -2, "setrotation");
	lua_pushcfunction(state, SCRIPT_Entity_SetScale);
	lua_setfield(state, -2, "setscale");
	lua_pushcfunction(state, SCRIPT_Entity_ForwardVector);
	lua_setfield(state, -2, "forwardvector");
	lua_pushcfunction(state, SCRIPT_Entity_RightVector);
	lua_setfield(state, -2, "rightvector");
	lua_pushcfunction(state, SCRIPT_Entity_UpVector);
	lua_setfield(state, -2, "upvector");
	lua_pushcfunction(state, SCRIPT_Entity_Translate);
	lua_setfield(state, -2, "translate");
	lua_pushcfunction(state, SCRIPT_Entity_TranslateLocal);
	lua_setfield(state, -2, "translatelocal");
	lua_pushcfunction(state, SCRIPT_Entity_Rotate);
	lua_setfield(state, -2, "rotate");
	lua_pushcfunction(state, SCRIPT_Entity_RotateLocal);
	lua_setfield(state, -2, "rotatelocal");
	lua_pushcfunction(state, SCRIPT_Entity_Scale);
	lua_setfield(state, -2, "scale");
	lua_pushcfunction(state, SCRIPT_Entity_ScaleAdd);
	lua_setfield(state, -2, "scaleadd");
	lua_pushcfunction(state, SCRIPT_Animation_SetKey);
	lua_setfield(state, -2, "setanimkey");
	lua_pushcfunction(state, SCRIPT_Audio_PlayEffect);
	lua_setfield(state, -2, "playeffect");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

