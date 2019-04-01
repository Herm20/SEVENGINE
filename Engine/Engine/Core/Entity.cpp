#include "Entity.h"

#include "Scene.h"
#include "Component.h"

void Entity::DestroyInternal()
{
	u64 cc = children.size();
	for (u64 i = 0; i < cc; ++i)
	{
		((Entity*)(children[i]))->Destroy();
	}

	if (parent != nullptr) { parent->RemoveChild(this); }

	// Safety block - maybe remove later for performance?
	children.clear();
	parent = nullptr;
	scene = SceneRef();

	// TODO : Perform component login here
}

Entity::Entity() :
	Object(),
	tags(),
	scene()
{
	// Nothing interesting to do here
}

Entity::Entity(Scene* parentScene, u64 ind, u64 sID, u64 tID, const Transform& t, Entity* parentEntity) :
	Object(t, parentEntity),
	tags(),
	scene(parentScene, ind, sID, tID)
{
	// Nothing interesting to do here
}

Entity::~Entity()
{
	// Nothing interesting to do here
}

void Entity::Destroy()
{
//	scene.GetScene()->DestroyEntity(this);
}

void Entity::AddTag(boost::container::string tag)
{
	// TODO : Add logic for interfacing scene - various tag optimizations
	tags.insert(tag);
}

void Entity::RemoveTag(boost::container::string tag)
{
	// TODO : Add logic for interfacing scene - various tag optimizations
	tags.erase(tag);
}

void Entity::AddTags(boost::unordered_set<boost::container::string> newTags)
{
	// TODO : Add logic for interfacing scene - various tag optimizations
	tags.merge(newTags);
}

void Entity::SetMesh()
{
}
