#ifndef BINDINGS_ENTITY_TRANSFORM_H_
#define BINDINGS_ENTITY_TRANSFORM_H_

#include "../BindingBase.h"

#include <glm/glm.hpp>
#include <cstdio>

extern "C" {
	int SCRIPT_SetEntityPosition(lua_State* state)
	{
		float x = luaL_checknumber(state, 1);
		float y = luaL_checknumber(state, 2);
		float z = luaL_checknumber(state, 3);

		SCRIPT_system->SetEntityPosition(glm::vec3(x, y, z));
		return 0;
	}
}

void ScriptSystem::SetEntityPosition(glm::vec3 newPos)
{
	ecs::TransformComponent& transform = manager.getComponentStore<ecs::TransformComponent>().get(currentEntity);
	transform.transform.SetPosition(newPos);
}

inline void SCRIPT_BIND_EntityTransform(lua_State* state)
{
	lua_pushcfunction(state, SCRIPT_SetEntityPosition);
	lua_setglobal(state, "setentityposition");
}

#endif

