#ifndef SCRIPTING_UTILITIES_H_
#define SCRIPTING_UTILITIES_H_

#include "BindingBase.h"

#include <glm/glm.hpp>
#include <cstdio>

inline bool lua_safecall(lua_State* state, int arg, int ret, const char* mes = "SCRIPT ERROR :")
{
	if (lua_pcall(state, arg, ret, 0))
	{
		printf("%s\n", mes);
		printf("%s\n", lua_tostring(state, -1));
		lua_pop(state, 1);
		return false;
	}

	return true;
}

inline void lua_swap(lua_State* state)
{
	lua_pushvalue(state, -2);
	lua_pushvalue(state, -2);
	lua_replace(state, -4);
	lua_replace(state, -2);
}

inline boost::container::string SCRIPT_UTIL_GetString(lua_State* state, int loc)
{
	if (!lua_istable(state, loc)) { return boost::container::string(""); }

	lua_pushnumber(state, 1);
	lua_gettable(state, loc > 0 ? loc : loc - 1);

	boost::container::string name = lua_isstring(state, -1) ? lua_tostring(state, -1) : boost::container::string("");

	lua_pop(state, 1);

	return name;
}

inline const char* SCRIPT_UTIL_GetCharString(lua_State* state, int loc)
{
	if (!lua_istable(state, loc)) { return ""; }

	lua_pushnumber(state, 1);
	lua_gettable(state, loc > 0 ? loc : loc - 1);

	const char* name = lua_isstring(state, -1) ? lua_tostring(state, -1) : "";

	lua_pop(state, 1);

	return name;
}

inline glm::vec3 SCRIPT_UTIL_GetVector(lua_State* state, int loc)
{
	if (!lua_istable(state, loc)) { return glm::vec3(); }

	lua_pushnumber(state, 1);
	lua_gettable(state, loc > 0 ? loc : loc - 1);
	lua_pushnumber(state, 2);
	lua_gettable(state, loc > 0 ? loc : loc - 2);
	lua_pushnumber(state, 3);
	lua_gettable(state, loc > 0 ? loc : loc - 3);

	float x = lua_isnumber(state, -3) ? lua_tonumber(state, -3) : 0.0f;
	float y = lua_isnumber(state, -2) ? lua_tonumber(state, -2) : 0.0f;
	float z = lua_isnumber(state, -1) ? lua_tonumber(state, -1) : 0.0f;

	lua_pop(state, 3);

	return glm::vec3(x, y, z);
}

inline glm::quat SCRIPT_UTIL_GetQuaternion(lua_State* state, int loc)
{
	if (!lua_istable(state, loc)) { return glm::identity<glm::quat>(); }

	lua_pushnumber(state, 1);
	lua_gettable(state, loc > 0 ? loc : loc - 1);
	lua_pushnumber(state, 2);
	lua_gettable(state, loc > 0 ? loc : loc - 2);
	lua_pushnumber(state, 3);
	lua_gettable(state, loc > 0 ? loc : loc - 3);
	lua_pushnumber(state, 4);
	lua_gettable(state, loc > 0 ? loc : loc - 4);

	if (!lua_isnumber(state, -4) ||
	    !lua_isnumber(state, -3) ||
	    !lua_isnumber(state, -2) ||
	    !lua_isnumber(state, -1))
	{
		return glm::identity<glm::quat>();
	}

	float x = lua_tonumber(state, -4);
	float y = lua_tonumber(state, -3);
	float z = lua_tonumber(state, -2);
	float w = lua_tonumber(state, -1);

	lua_pop(state, 4);

	// Who designed this such that values go in WXYZ, but come out XYZW???
	return glm::quat(w, x, y, z);
}

inline void SCRIPT_UTIL_PushVector(lua_State* state, glm::vec3 vec)
{
	lua_createtable(state, 3, 0);

	lua_pushnumber(state, 1);
	lua_pushnumber(state, vec[0]);
	lua_settable(state, -3);
	lua_pushnumber(state, 2);
	lua_pushnumber(state, vec[1]);
	lua_settable(state, -3);
	lua_pushnumber(state, 3);
	lua_pushnumber(state, vec[2]);
	lua_settable(state, -3);
}

inline void SCRIPT_UTIL_PushQuaternion(lua_State* state, glm::quat quat)
{
	lua_createtable(state, 4, 0);

	lua_pushnumber(state, 1);
	lua_pushnumber(state, quat[0]);
	lua_settable(state, -3);
	lua_pushnumber(state, 2);
	lua_pushnumber(state, quat[1]);
	lua_settable(state, -3);
	lua_pushnumber(state, 3);
	lua_pushnumber(state, quat[2]);
	lua_settable(state, -3);
	lua_pushnumber(state, 4);
	lua_pushnumber(state, quat[3]);
	lua_settable(state, -3);
}

#endif



