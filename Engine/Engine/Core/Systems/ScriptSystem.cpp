#include "ScriptSystem.h"

#include <glm/glm.hpp>
#include <cstdio>

#include "../Scripting/Bindings.h"
#include "../Scripting/Utilities.h"

// PRIVATE

void ScriptSystem::LoadScript(ecs::Entity entity, ecs::ScriptComponent& script)
{
	const char* cstr = script.path.c_str();
	if (luaL_loadfile(state, cstr))
	{
		printf("Lua load error\n");
	    printf("%s\n", lua_tostring(state, -1));
	    lua_pop(state,1);
	}

	lua_safecall(state, 0, LUA_MULTRET, "SCRIPT LOAD FAILURE :");

	// Attempt to fetch the script table
	lua_getglobal(state, "scripts");
	lua_pushnumber(state, script.id);
	lua_gettable(state, -2);

	// Script needs to be created (first load)
	if (lua_isnil(state, -1))
	{
		// Pop the nil value
		lua_pop(state, 1);

		// Create the table for the script
		lua_pushnumber(state, script.id);
		lua_newtable(state);
		lua_settable(state, -3);

		// Put the new table on the top of the stack
		lua_pushnumber(state, script.id);
		lua_gettable(state, -2);

		// Push IDs into the object
		lua_pushnumber(state, entity);
		lua_setfield(state, -2, "entityid");
		lua_pushnumber(state, script.id);
		lua_setfield(state, -2, "scriptid");
	}

	// Reduce the stack to the currently relevant script table
	lua_remove(state, -2);

	// Push known event functions from the load into the script table
	lua_getglobal(state, "init");
	lua_setfield(state, -2, "init");
	lua_getglobal(state, "update");
	lua_setfield(state, -2, "update");
	lua_getglobal(state, "onmessage");
	lua_setfield(state, -2, "onmessage");

	// Clear the stack
	lua_pop(state, 1);
}

// PUBLIC

ScriptSystem::ScriptSystem(ecs::Manager& manager) :
	ecs::System(manager),
	state(nullptr),
	nextID(1),
	currentEntity(0)
{
	ecs::ComponentTypeSet requiredComponents;
	ecs::ComponentType ctype = ecs::ScriptComponent::_mType;
	requiredComponents.insert(ctype);
	setRequiredComponents(std::move(requiredComponents));
}

ScriptSystem::~ScriptSystem()
{

}

void ScriptSystem::Init()
{
	SCRIPT_system = this;

	state = luaL_newstate();
	luaL_openlibs(state);

	SCRIPT_BIND_PushBindings(state);

	lua_newtable(state);
	lua_setglobal(state, "scripts");
}

void ScriptSystem::Destroy()
{
	lua_close(state);
}

void ScriptSystem::ReloadScripts()
{
	ecs::ComponentStore<ecs::ScriptComponent>& scripts = manager.getComponentStore<ecs::ScriptComponent>();
	std::unordered_map<ecs::Entity, ecs::ScriptComponent> components = scripts.getComponents();

	for (auto i : components)
	{
		LoadScript(i.first, i.second);
	}
}

void ScriptSystem::startFrame(float dt)
{
}

void ScriptSystem::updateEntity(float dt, ecs::Entity entity)
{
	currentEntity = entity;
	ecs::ScriptComponent& script = manager.getComponentStore<ecs::ScriptComponent>().get(currentEntity);

	if (script.id == U64_MAX)
	{
		script.id = nextID;
		++nextID;

		LoadScript(entity, script);

		// Get the script table's init function
		lua_getglobal(state, "scripts");
		lua_pushnumber(state, script.id);
		lua_gettable(state, -2);
		lua_getfield(state, -1, "init");

		// Swap the position of the function and the table
		lua_swap(state);

		// Call init with the script table as the only argument
		lua_safecall(state, 1, 0, "SCRIPT INIT ERROR :");

		// Remove scripts from the stack
		lua_pop(state, 1);
	}

	// Get the script table's update function
	lua_getglobal(state, "scripts");
	lua_pushnumber(state, script.id);
	lua_gettable(state, -2);
	lua_getfield(state, -1, "update");

	// Swap the position of the function and the table
	lua_pushvalue(state, -2);
	lua_pushvalue(state, -2);
	lua_replace(state, -4);
	lua_replace(state, -2);

	lua_pushnumber(state, dt);
	lua_safecall(state, 2, 0);

	lua_pop(state, 1);
}

void ScriptSystem::endFrame(float dt)
{
}

void ScriptSystem::SendMessage(ecs::Entity entity, u64 script_id, const boost::container::string& message, const boost::container::string& data)
{
	currentEntity = entity;
	ecs::ScriptComponent& script = manager.getComponentStore<ecs::ScriptComponent>().get(currentEntity);

	// There's probably a cleaner way to do this, but for now it works
	boost::container::string dc = boost::container::string("data = ") + data;
	luaL_dostring(state, dc.c_str());

	// Get the script table's onmessage function
	lua_getglobal(state, "scripts");
	lua_pushnumber(state, script_id);
	lua_gettable(state, -2);
	lua_getfield(state, -1, "onmessage");

	// Swap the position of the function and the table
	lua_pushvalue(state, -2);
	lua_pushvalue(state, -2);
	lua_replace(state, -4);
	lua_replace(state, -2);

	lua_pushstring(state, message.c_str());
	lua_getglobal(state, "data");

	lua_safecall(state, 3, 0);

	lua_pop(state, 2);
}

