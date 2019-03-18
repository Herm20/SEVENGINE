#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include "Types.h"

class Entity;

/*! \class Component
*  \brief Base class for components
*/
class Component
{
private:
	Entity* entity;

public:
	Component(Entity* ent);
	Component(const Component &c);
	~Component();
	inline Entity* GetEntity() { return entity; }
	const Component & operator=(const Component &c);
};

#endif
