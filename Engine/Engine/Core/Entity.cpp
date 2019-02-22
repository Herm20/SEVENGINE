#include "Entity.h"

Entity::Entity() :
	Object(),
	tags()
{
	// Nothing interesting to do here
}

Entity::Entity(const Transform& t, Entity* parentEntity) :
	Object(t, parentEntity),
	tags()
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
	tags.push_back(tag);
}

void Entity::RemoveTag(boost::container::string tag)
{
	// TODO : Add logic for interfacing scene - various tag optimizations
	u64 j = tags.size();
	for (u64 i = 0; i < j; ++i)
	{
		if (tags[i] == tag)
		{
			tags[i] = tags[j - 1];
			tags.pop_back();
			break;
		}
	}
}