#ifndef BINDINGS_CAMERA_H_
#define BINDINGS_CAMERA_H_

#include "../BindingBase.h"
#include "../Utilities.h"

#include "../../Application.h"

#include <cstdio>

extern "C" {
	int SCRIPT_Camera_GetPosition(lua_State* state)
	{
		SCRIPT_UTIL_PushVector(state, SCRIPT_system->cam->GetPosition());
		return 1;
	}

	int SCRIPT_Camera_GetRotation(lua_State* state)
	{
		SCRIPT_UTIL_PushVector(state, SCRIPT_system->cam->GetRotation());
		return 1;
	}

	int SCRIPT_Camera_GetVelocity(lua_State* state)
	{
		SCRIPT_UTIL_PushVector(state, SCRIPT_system->cam->GetVelocity());
		return 1;
	}

	int SCRIPT_Camera_SetPosition(lua_State* state)
	{
		SCRIPT_system->cam->SetPosition(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Camera_SetRotation(lua_State* state)
	{
		SCRIPT_system->cam->SetRotation(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}

	int SCRIPT_Camera_SetVelocity(lua_State* state)
	{
		SCRIPT_system->cam->SetVelocity(SCRIPT_UTIL_GetVector(state, 1));
		return 0;
	}
}

inline void SCRIPT_BIND_Camera(lua_State* state)
{
	lua_newtable(state);
	lua_setglobal(state, "camera");
	lua_getglobal(state, "camera");

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_Camera_GetPosition);
	lua_setfield(state, -2, "getposition");
	lua_pushcfunction(state, SCRIPT_Camera_GetRotation);
	lua_setfield(state, -2, "getrotation");
	lua_pushcfunction(state, SCRIPT_Camera_GetVelocity);
	lua_setfield(state, -2, "getvelocity");
	lua_pushcfunction(state, SCRIPT_Camera_SetPosition);
	lua_setfield(state, -2, "setposition");
	lua_pushcfunction(state, SCRIPT_Camera_SetRotation);
	lua_setfield(state, -2, "setrotation");
	lua_pushcfunction(state, SCRIPT_Camera_SetVelocity);
	lua_setfield(state, -2, "setvelocity");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

