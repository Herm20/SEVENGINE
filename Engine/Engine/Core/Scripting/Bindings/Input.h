#ifndef BINDINGS_INPUT_H_
#define BINDINGS_INPUT_H_

#include "../BindingBase.h"
#include "../../InputPoller.h"

#include <cstdio>

extern "C" {
	int SCRIPT_Input_GetKey(lua_State* state)
	{
		// Get the input
		if (!lua_isnumber(state, 1))
		{
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, Input::GetKey(lua_tonumber(state, 1)));

		return 1;
	}
}

inline void SCRIPT_Input_CreateKeys(lua_State* state)
{
	lua_newtable(state);
	lua_setfield(state, -2, "keys");
	lua_getfield(state, -1, "keys");

	char sk[2];
	sk[1] = 0;
	for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; ++i)
	{
		lua_pushnumber(state, i);
		sk[0] = 'a' + i - GLFW_KEY_A;
		lua_setfield(state, -2, sk);
	}

	lua_pop(state, 1);
}

inline void SCRIPT_BIND_Input(lua_State* state)
{
	lua_newtable(state);
	lua_setglobal(state, "input");
	lua_getglobal(state, "input");

	SCRIPT_Input_CreateKeys(state);

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_Input_GetKey);
	lua_setfield(state, -2, "getkey");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

