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
	// Index at which the entity will be spawned into the entities array
	u64 index;

	// If there is an open spot in the entity array, insert the new entity into it
	if (entityArrayGaps.size() != 0)
	{
		index = entityArrayGaps[entityArrayGaps.size() - 1];
		entityArrayGaps.pop_back();
		entities[index] = Entity(this, index, entitiesAll.size(), parent == nullptr ? entitiesTop.size() : U64_MAX, transform, parent);
	}
	// Otherwise, add to the end of the array
	else
	{
		index = entities.size();
		entities.emplace_back(this, index, entitiesAll.size(), parent == nullptr ? entitiesTop.size() : U64_MAX, transform, parent);
	}

	// Handle pointer referencing for the new entity
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

		// Actual mechanism for allowing the entity to free any references etc.
		entity->DestroyInternal();

		// Consider the position of the entity in the array to be an open spot for future spawns
		entityArrayGaps.push_back(reference.index);

		// Reclaim the reference points for other entities, to avoid creating gaps in them
		entitiesAll[reference.sceneID] = entitiesAll[entitiesAll.size() - 1];
		entitiesAll[reference.sceneID]->scene.sceneID = reference.sceneID;
		entitiesAll.pop_back();

		// Same as before, but only for top-level (parent-less)
		if (entitiesTop[reference.topID] != U64_MAX)
		{
			entitiesTop[reference.topID] = entitiesTop[entitiesTop.size() - 1];
			entitiesTop[reference.topID]->scene.topID = reference.topID;
			entitiesTop.pop_back();
		}
	}
}
