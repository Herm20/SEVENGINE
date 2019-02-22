#ifndef ENTITY_H_
#define ENTITY_H_

#include "Object.h"

class Entity : public Object
{
private:
	boost::container::vector<boost::container::string> tags;

	// Scene and component stuff goes here
public:
	Entity();
	Entity(const Transform& t, Entity* parentEntity = nullptr);
	~Entity();

	void Destroy() override;

	// Will probably move tag system purely into script-side once that's up-and-running
	void AddTag(boost::container::string tag);
	void RemoveTag(boost::container::string tag);

	// Scene and component stuff goes here
};

#endif