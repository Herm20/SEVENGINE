#include "Entity.h"

#include "Component.h"

Entity::Entity() :
	Object(),
	tags(),
	scene()
{
	// Nothing interesting to do here
}

Entity::Entity(Scene* parentScene, u64 sID, u64 tID, const Transform& t, Entity* parentEntity) :
	Object(t, parentEntity),
	tags(),
	scene(parentScene, sID, tID)
{
	// Nothing interesting to do here
}

Entity::~Entity()
{
	// Nothing interesting to do here
}

void Entity::Destroy()
{
	Object::Destroy();
	// TODO : Perform any scene and compoenent cleanup here
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
