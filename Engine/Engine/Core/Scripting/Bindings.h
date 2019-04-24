#ifndef BINDINGS_H_
#define BINDINGS_H_

#include "BindingBase.h"
#include "Bindings/Math.h"
#include "Bindings/EntityTransform.h"

inline void SCRIPT_BIND_PushBindings(lua_State* state)
{
	SCRIPT_BIND_Math(state);
	SCRIPT_BIND_EntityTransform(state);
}

#endif

