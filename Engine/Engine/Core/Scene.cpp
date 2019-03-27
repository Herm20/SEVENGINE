#include "Scene.h"

Scene::Scene() :
	entities(),
	entitiesTop(),
	entitiesAll()
{
	// Nothing interesting to do here
}

Scene::~Scene()
{
	// Nothing interesting to do here
}

Entity* Scene::SpawnEntity(Entity* parent, const Transform& transform)
{
	u64 index = entities.size();
	entities.emplace_back(this, index, transform, parent);
	Entity* spawned = entities[index];

	if (parent == nullptr) { entitiesTop.push_back(spawned); }
	entitiesAll.push_back(spawned);
	return spawned;
}

void Scene::DestroyEntity(Entity* entity)
{
	// TODO : Sort out which direction destruction happens (scene to entity vs entity to scene)
}
