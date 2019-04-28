#ifndef BINDINGS_MATH_H_
#define BINDINGS_MATH_H_

#include "../BindingBase.h"
#include "../Utilities.h"

#include <glm/glm.hpp>
#include <cstdio>

extern "C" {
	int SCRIPT_Math_AxisAngle(lua_State* state)
	{
		glm::vec3 axis = SCRIPT_UTIL_GetVector(state, 1);
		float angle = lua_isnumber(state, 2) ? lua_tonumber(state, 2) : 0.0f;
		SCRIPT_UTIL_PushQuaternion(state, glm::angleAxis(angle, axis));

		return 1;
	}

	int SCRIPT_Math_EulerAngles(lua_State* state)
	{
		glm::vec3 angles = SCRIPT_UTIL_GetVector(state, 1);
		SCRIPT_UTIL_PushQuaternion(state, glm::quat(angles));

		return 1;
	}
}

inline void SCRIPT_BIND_Math(lua_State* state)
{
	lua_getglobal(state, "math");

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_Math_AxisAngle);
	lua_setfield(state, -2, "axisangle");
	lua_pushcfunction(state, SCRIPT_Math_EulerAngles);
	lua_setfield(state, -2, "eulerangles");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

