#include "Component.h"

Component::Component(Entity* ent) :
	entity(ent)
{

}

Component::Component(const Component &c)
{
	this->entity = c.entity;
}

Component::~Component()
{

}

const Component & Component::operator=(const Component &c)
{
	this->entity = c.entity;

	return *this;
}
