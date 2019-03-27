#ifndef SCENE_H_
#define SCENE_H_

#include "Entity.h"

#include <boost/container/vector.hpp>

class Scene
{
private:
	boost::container::vector<Entity> entities;
	boost::container::vector<Entity*> entitiesTop;
	boost::container::vector<Entity*> entitiesAll;

public:
	Scene();
	~Scene();

	Entity* SpawnEntity(Entity* parent = nullptr, const Transform& transform = Transform());

	void DestroyEntity(Entity* entity);
};

#endif /* SCENE_H_ */
