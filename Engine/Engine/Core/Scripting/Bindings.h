#ifndef BINDINGS_H_
#define BINDINGS_H_

#include "BindingBase.h"
#include "Bindings/Math.h"
#include "Bindings/Input.h"
#include "Bindings/World.h"
#include "Bindings/Camera.h"
#include "Bindings/EntityTransform.h"

inline void SCRIPT_BIND_PushBindings(lua_State* state)
{
	SCRIPT_BIND_Math(state);
	SCRIPT_BIND_EntityTransform(state);
	SCRIPT_BIND_Input(state);
	SCRIPT_BIND_World(state);
	SCRIPT_BIND_Camera(state);
}

#endif

