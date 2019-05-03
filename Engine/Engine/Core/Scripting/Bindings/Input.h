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

	int SCRIPT_Input_GetKeyDown(lua_State* state)
	{
		// Get the input
		if (!lua_isnumber(state, 1))
		{
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, Input::GetKeyDown(lua_tonumber(state, 1)));

		return 1;
	}

	int SCRIPT_Input_GetKeyUp(lua_State* state)
	{
		// Get the input
		if (!lua_isnumber(state, 1))
		{
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, Input::GetKeyUp(lua_tonumber(state, 1)));

		return 1;
	}
}

inline void SCRIPT_Input_CreateKeys(lua_State* state)
{
	lua_newtable(state);
	lua_setfield(state, -2, "keys");
	lua_getfield(state, -1, "keys");

	// Cute little string hack
	char sk[4] = { 0, 0, 0, 0 };

	// Letter keys
	for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; ++i)
	{
		lua_pushnumber(state, i);
		sk[0] = 'a' + i - GLFW_KEY_A;
		lua_setfield(state, -2, sk);
	}

	// Numeric keys
	for (int i = GLFW_KEY_0; i <= GLFW_KEY_9; ++i)
	{
		lua_pushnumber(state, i);
		sk[0] = '0' + i - GLFW_KEY_0;
		lua_setfield(state, -2, sk);
	}

	// Function keys (only allow 12)
	sk[0] = 'f';
	for (int i = GLFW_KEY_F1; i <= GLFW_KEY_F9; ++i)
	{
		lua_pushnumber(state, i);
		sk[1] = '0' + i - GLFW_KEY_F1;
		lua_setfield(state, -2, sk);
	}
	sk[1] = '1';
	for (int i = GLFW_KEY_F10; i <= GLFW_KEY_F12; ++i)
	{
		lua_pushnumber(state, i);
		sk[2] = '0' + i - GLFW_KEY_F10;
		lua_setfield(state, -2, sk);
	}

	// Keypad keys
	sk[0] = 'k';
	sk[1] = 'p';
	for (int i = GLFW_KEY_KP_0; i <= GLFW_KEY_KP_9; ++i)
	{
		lua_pushnumber(state, i);
		sk[2] = '0' + i - GLFW_KEY_KP_0;
		lua_setfield(state, -2, sk);
	}

	lua_pushnumber(state, GLFW_KEY_SPACE);
	lua_setfield(state, -2, "space");
	lua_pushnumber(state, GLFW_KEY_COMMA);
	lua_setfield(state, -2, "comma");
	lua_pushnumber(state, GLFW_KEY_PERIOD);
	lua_setfield(state, -2, "period");
	lua_pushnumber(state, GLFW_KEY_SLASH);
	lua_setfield(state, -2, "slash");
	lua_pushnumber(state, GLFW_KEY_SEMICOLON);
	lua_setfield(state, -2, "semicolon");
	lua_pushnumber(state, GLFW_KEY_APOSTROPHE);
	lua_setfield(state, -2, "apostrophe");
	lua_pushnumber(state, GLFW_KEY_LEFT_BRACKET);
	lua_setfield(state, -2, "leftbracket");
	lua_pushnumber(state, GLFW_KEY_RIGHT_BRACKET);
	lua_setfield(state, -2, "rightbracket");
	lua_pushnumber(state, GLFW_KEY_BACKSLASH);
	lua_setfield(state, -2, "backslash");
	lua_pushnumber(state, GLFW_KEY_GRAVE_ACCENT);
	lua_setfield(state, -2, "tick");
	lua_pushnumber(state, GLFW_KEY_MINUS);
	lua_setfield(state, -2, "minus");
	lua_pushnumber(state, GLFW_KEY_EQUAL);
	lua_setfield(state, -2, "equal");

	lua_pushnumber(state, GLFW_KEY_ESCAPE);
	lua_setfield(state, -2, "escape");
	lua_pushnumber(state, GLFW_KEY_ENTER);
	lua_setfield(state, -2, "enter");
	lua_pushnumber(state, GLFW_KEY_TAB);
	lua_setfield(state, -2, "tab");
	lua_pushnumber(state, GLFW_KEY_BACKSPACE);
	lua_setfield(state, -2, "backspace");
	lua_pushnumber(state, GLFW_KEY_INSERT);
	lua_setfield(state, -2, "insert");
	lua_pushnumber(state, GLFW_KEY_DELETE);
	lua_setfield(state, -2, "delete");
	lua_pushnumber(state, GLFW_KEY_LEFT);
	lua_setfield(state, -2, "left");
	lua_pushnumber(state, GLFW_KEY_RIGHT);
	lua_setfield(state, -2, "right");
	lua_pushnumber(state, GLFW_KEY_UP);
	lua_setfield(state, -2, "up");
	lua_pushnumber(state, GLFW_KEY_DOWN);
	lua_setfield(state, -2, "down");
	lua_pushnumber(state, GLFW_KEY_PAGE_UP);
	lua_setfield(state, -2, "pageup");
	lua_pushnumber(state, GLFW_KEY_PAGE_DOWN);
	lua_setfield(state, -2, "pagedown");
	lua_pushnumber(state, GLFW_KEY_HOME);
	lua_setfield(state, -2, "home");
	lua_pushnumber(state, GLFW_KEY_END);
	lua_setfield(state, -2, "end");
	lua_pushnumber(state, GLFW_KEY_CAPS_LOCK);
	lua_setfield(state, -2, "capslock");
	lua_pushnumber(state, GLFW_KEY_NUM_LOCK);
	lua_setfield(state, -2, "numlock");
	lua_pushnumber(state, GLFW_KEY_SCROLL_LOCK);
	lua_setfield(state, -2, "scrolllock");
	lua_pushnumber(state, GLFW_KEY_PRINT_SCREEN);
	lua_setfield(state, -2, "printscreen");
	lua_pushnumber(state, GLFW_KEY_PAUSE);
	lua_setfield(state, -2, "pause");

	lua_pushnumber(state, GLFW_KEY_KP_DECIMAL);
	lua_setfield(state, -2, "kpdecimal");
	lua_pushnumber(state, GLFW_KEY_KP_ADD);
	lua_setfield(state, -2, "kpadd");
	lua_pushnumber(state, GLFW_KEY_KP_SUBTRACT);
	lua_setfield(state, -2, "kpsubtract");
	lua_pushnumber(state, GLFW_KEY_KP_MULTIPLY);
	lua_setfield(state, -2, "kpmultiply");
	lua_pushnumber(state, GLFW_KEY_KP_DIVIDE);
	lua_setfield(state, -2, "kpdivide");
	lua_pushnumber(state, GLFW_KEY_KP_ENTER);
	lua_setfield(state, -2, "kpenter");
	lua_pushnumber(state, GLFW_KEY_KP_EQUAL);
	lua_setfield(state, -2, "kpequal");

	lua_pushnumber(state, GLFW_KEY_LEFT_CONTROL);
	lua_setfield(state, -2, "leftcontrol");
	lua_pushnumber(state, GLFW_KEY_LEFT_ALT);
	lua_setfield(state, -2, "leftalt");
	lua_pushnumber(state, GLFW_KEY_LEFT_SHIFT);
	lua_setfield(state, -2, "leftshift");
	lua_pushnumber(state, GLFW_KEY_RIGHT_CONTROL);
	lua_setfield(state, -2, "rightcontrol");
	lua_pushnumber(state, GLFW_KEY_RIGHT_ALT);
	lua_setfield(state, -2, "rightalt");
	lua_pushnumber(state, GLFW_KEY_RIGHT_SHIFT);
	lua_setfield(state, -2, "rightshift");
	lua_pushnumber(state, GLFW_KEY_MENU);
	lua_setfield(state, -2, "menu");

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
	lua_pushcfunction(state, SCRIPT_Input_GetKeyDown);
	lua_setfield(state, -2, "getkeydown");
	lua_pushcfunction(state, SCRIPT_Input_GetKeyUp);
	lua_setfield(state, -2, "getkeyup");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

