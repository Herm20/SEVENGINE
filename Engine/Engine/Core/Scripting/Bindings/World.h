#ifndef BINDINGS_WORLD_H_
#define BINDINGS_WORLD_H_

#include "../BindingBase.h"
#include "../Utilities.h"

#include <cstdio>

extern "C" {
	int SCRIPT_World_SendMessage(lua_State* state)
	{
		ecs::Entity orig = SCRIPT_system->currentEntity;

		// Get the input
		if (!lua_isnumber(state, 1) || !lua_isnumber(state, 2) || !lua_isstring(state, 3) || lua_isnone(state, 4))
		{
			return 0;
		}

		SCRIPT_system->currentEntity = lua_tonumber(state, 1);
		u64 script_id = lua_tonumber(state, 2);

		// Fetch the script and call its onmessage function
		lua_getglobal(state, "scripts");
		lua_pushnumber(state, script_id);
		lua_gettable(state, -2);
		lua_remove(state, -2);
		if (lua_isnil(state, -1)) { lua_pop(state, 1); return 0; }

		lua_getfield(state, -1, "onmessage");
		lua_swap(state);
		lua_pushvalue(state, 3);
		lua_pushvalue(state, 4);

		lua_safecall(state, 3, 0);

		SCRIPT_system->currentEntity = orig;

		return 0;
	}
}

inline void SCRIPT_BIND_World(lua_State* state)
{
	lua_newtable(state);
	lua_setglobal(state, "world");
	lua_getglobal(state, "world");

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_World_SendMessage);
	lua_setfield(state, -2, "sendmessage");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

