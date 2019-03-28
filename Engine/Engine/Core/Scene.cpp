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
	u64 index = entitiesAll.size();
	entities.emplace_back(this, index, parent == nullptr ? entitiesTop.size() : U64_MAX, transform, parent);
	Entity* spawned = &(entities[index]);

	if (parent == nullptr) { entitiesTop.push_back(spawned); }
	entitiesAll.push_back(spawned);
	return spawned;
}

void Scene::DestroyEntity(Entity* entity)
{
	// TODO : Something more elegant here
	if (entity->scene.GetScene() == this)
	{
		SceneRef reference = entity->scene;
		entity->DestroyInternal();

		entityArrayGaps.push_back(reference.index);

		entitiesAll[reference.sceneID] = entitiesAll[entitiesAll.size() - 1];
		entitiesAll[reference.sceneID]->scene.sceneID = reference.sceneID;
		entitiesAll.pop_back();

		if (entitiesTop[reference.topID] != U64_MAX)
		{
			entitiesTop[reference.topID] = entitiesTop[entitiesTop.size() - 1];
			entitiesTop[reference.topID]->scene.topID = reference.topID;
			entitiesTop.pop_back();
		}
	}
}
