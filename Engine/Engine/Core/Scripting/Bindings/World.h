#ifndef BINDINGS_WORLD_H_
#define BINDINGS_WORLD_H_

#include "../BindingBase.h"
#include "../Utilities.h"

#include "../../AssetManager.h"
#include "../../Animation.h"

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

	int SCRIPT_World_SpawnEntity(lua_State* state)
	{
		if (!lua_istable(state, 1)) { return 0; }
		SCRIPT_system->SCRIPT_World_SpawnEntity();

		return 1;
	}

	int SCRIPT_World_DestroyEntity(lua_State* state)
	{
		if (!lua_isnumber(state, 1)) { return 0; }
		SCRIPT_system->SCRIPT_World_DestroyEntity(lua_tonumber(state, 1));

		return 0;
	}
}

void SCRIPT_World_SpawnEntity_TransformComponent(lua_State* state, ecs::TransformComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));

		if (ckey == boost::container::string("position"))
			comp.transform.SetPosition(SCRIPT_UTIL_GetVector(state, -1));
		else if (ckey == boost::container::string("rotation"))
			comp.transform.SetRotation(SCRIPT_UTIL_GetQuaternion(state, -1));
		else if (ckey == boost::container::string("scale"))
			comp.transform.SetScale(SCRIPT_UTIL_GetVector(state, -1));

		lua_pop(state, 1);
	}
}

void SCRIPT_World_SpawnEntity_MeshRendererComponent(lua_State* state, AssetManager* assetMan, ecs::MeshRendererComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));

		if (ckey == boost::container::string("mesh"))
			comp.mesh = boost::shared_ptr<Mesh>(new Mesh(assetMan->GetMesh(lua_tostring(state, -1))));
		else if (ckey == boost::container::string("material"))
			comp.material = assetMan->GetMaterial(lua_tostring(state, -1));

		lua_pop(state, 1);
	}
}

void SCRIPT_World_SpawnEntity_RigidBodyComponent(lua_State* state, ecs::RigidBodyComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));

		if (ckey == boost::container::string("velocity"))
			comp.velocity = SCRIPT_UTIL_GetVector(state, -1);

		lua_pop(state, 1);
	}
}

void SCRIPT_World_SpawnEntity_LightComponent(lua_State* state, ecs::LightComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));

		if (ckey == boost::container::string("position"))
			comp.light.pos = SCRIPT_UTIL_GetVector(state, -1);
		else if (ckey == boost::container::string("direction"))
			comp.light.dir = SCRIPT_UTIL_GetVector(state, -1);
		else if (ckey == boost::container::string("color"))
			comp.light.color = SCRIPT_UTIL_GetVector(state, -1);
		else if (ckey == boost::container::string("radius"))
			comp.light.radius = lua_tonumber(state, -1);
		else if (ckey == boost::container::string("intensity"))
			comp.light.intensity = lua_tonumber(state, -1);

		lua_pop(state, 1);
	}
}

void SCRIPT_World_SpawnEntity_ScriptComponent(lua_State* state, ecs::ScriptComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));

		if (ckey == boost::container::string("path"))
			comp.path = boost::container::string(lua_tostring(state, -1));

		lua_pop(state, 1);
	}
}

void SCRIPT_World_SpawnEntity_SpriteSheetComponent_Animations(lua_State* state, ecs::SpriteSheetComponent& comp)
{
	lua_pushnil(state);
	Animation anim;

	while (lua_next(state, -2))
	{
		lua_getfield(state, -1, "rate");
		anim.animRate = lua_tonumber(state, -1);
		lua_pop(state, 1);

		lua_getfield(state, -1, "startframe");
		anim.startFrame = (int)(lua_tonumber(state, -1));
		lua_pop(state, 1);

		lua_getfield(state, -1, "endframe");
		anim.endFrame = (int)(lua_tonumber(state, -1));
		lua_pop(state, 1);

		lua_getfield(state, -1, "loops");
		anim.doesLoop = lua_toboolean(state, -1);
		lua_pop(state, 1);

		comp.animations[lua_tostring(state, -2)] = anim;

		lua_pop(state, 1);
	}
}

void SCRIPT_Animation_SetKey(lua_State* state, boost::container::string key, ecs::SpriteSheetComponent& comp)
{
	lua_pushnil(state);

	comp.currentAnimationId = key;

	lua_pop(state, 1);
}

void SCRIPT_World_SpawnEntity_SpriteSheetComponent(lua_State* state, AssetManager* assetMan, ecs::SpriteSheetComponent& comp)
{
	lua_pushnil(state);

	glm::vec3 size;
	boost::container::string texName;
	boost::container::string animKey;

	while (lua_next(state, -2))
	{
		boost::container::string ckey = boost::container::string(lua_tostring(state, -2));

		if (ckey == boost::container::string("size"))
			size = SCRIPT_UTIL_GetVector(state, -1);
		else if (ckey == boost::container::string("texture"))
			texName = boost::container::string(lua_tostring(state, -1));
		else if (ckey == boost::container::string("animations"))
			SCRIPT_World_SpawnEntity_SpriteSheetComponent_Animations(state, comp);
		else if (ckey == boost::container::string("animkey"))
		{
			animKey = boost::container::string(lua_tostring(state, -1));
			SCRIPT_Animation_SetKey(state, animKey, comp);
		}

		lua_pop(state, 1);
	}

	comp.ss.Generate(glm::uvec2(size.x, size.y), assetMan->GetTexture(texName));
}
	
void SCRIPT_World_SpawnEntity_ColliderComponent(lua_State* state, ecs::ColliderComponent& comp)
{
	lua_pushnil(state);
	while (lua_next(state, -2))
	{
		boost::container::string ckey(lua_tostring(state, -2));
		if (ckey == boost::container::string("type"))
		{
			const char* val = lua_tostring(state, -1);
			if (val[1] == 'i') { comp.type = ecs::ColliderType::Hitbox; }
			else if (val[1] == 'u') { comp.type = ecs::ColliderType::Hurtbox; }
			else if (val[1] == 'r') { comp.type = ecs::ColliderType::Grabbox; }
		}
		else if (ckey == boost::container::string("shape"))
		{
			const char* val = lua_tostring(state, -1);
			if (val[0] == 'c') { comp.shape = ecs::ColliderShape::Cube; }
			else if (val[0] == 's') { comp.shape = ecs::ColliderShape::Sphere; }
		}
		else if (ckey == boost::container::string("offset")) {
			comp.offset = SCRIPT_UTIL_GetVector(state, -1);
		}
		else if (ckey == boost::container::string("scale")) {
			comp.scale = SCRIPT_UTIL_GetVector(state, -1);
		}

		lua_pop(state, 1);
	}

}

void ScriptSystem::SCRIPT_World_SpawnEntity()
{
	ecs::Entity spawned = manager.createEntity();

	lua_pushnil(state);
	while (lua_next(state, 1))
	{
		boost::container::string ekey(lua_tostring(state, -2));

		if (ekey == boost::container::string("transform"))
		{
			manager.addComponent(spawned, ecs::TransformComponent());
			SCRIPT_World_SpawnEntity_TransformComponent(state, manager.getComponentStore<ecs::TransformComponent>().get(spawned));
		}
		else if (ekey == boost::container::string("meshrenderer"))
		{
			manager.addComponent(spawned, ecs::MeshRendererComponent());
			SCRIPT_World_SpawnEntity_MeshRendererComponent(state, assetMan, manager.getComponentStore<ecs::MeshRendererComponent>().get(spawned));
		}
		else if (ekey == boost::container::string("rigidbody"))
		{
			manager.addComponent(spawned, ecs::RigidBodyComponent());
			SCRIPT_World_SpawnEntity_RigidBodyComponent(state, manager.getComponentStore<ecs::RigidBodyComponent>().get(spawned));
		}
		else if (ekey == boost::container::string("light"))
		{
			manager.addComponent(spawned, ecs::LightComponent());
			SCRIPT_World_SpawnEntity_LightComponent(state, manager.getComponentStore<ecs::LightComponent>().get(spawned));
		}
		else if (ekey == boost::container::string("collider"))
		{
			manager.addComponent(spawned, ecs::ColliderComponent());
			SCRIPT_World_SpawnEntity_ColliderComponent(state, manager.getComponentStore<ecs::ColliderComponent>().get(spawned));
		}
		else if (ekey == boost::container::string("script"))
		{
			manager.addComponent(spawned, ecs::ScriptComponent());
			SCRIPT_World_SpawnEntity_ScriptComponent(state, manager.getComponentStore<ecs::ScriptComponent>().get(spawned));
		}
		
		else if (ekey == boost::container::string("spritesheet"))
		{
			manager.addComponent(spawned, ecs::SpriteSheetComponent());
			SCRIPT_World_SpawnEntity_SpriteSheetComponent(state, assetMan, manager.getComponentStore<ecs::SpriteSheetComponent>().get(spawned));
		}

		lua_pop(state, 1);
	}

	manager.registerEntity(spawned);
	lua_pushnumber(state, spawned);
}

void ScriptSystem::SCRIPT_World_DestroyEntity(ecs::Entity entity)
{
	manager.unregisterEntity(entity);
}

inline void SCRIPT_BIND_World(lua_State* state)
{
	lua_newtable(state);
	lua_setglobal(state, "world");
	lua_getglobal(state, "world");

	// Push the functions and add them to the library table
	lua_pushcfunction(state, SCRIPT_World_SendMessage);
	lua_setfield(state, -2, "sendmessage");
	lua_pushcfunction(state, SCRIPT_World_SpawnEntity);
	lua_setfield(state, -2, "spawnentity");
	lua_pushcfunction(state, SCRIPT_World_DestroyEntity);
	lua_setfield(state, -2, "destroyentity");

	// Pop the library table back off the stack
	lua_pop(state, 1);
}

#endif

