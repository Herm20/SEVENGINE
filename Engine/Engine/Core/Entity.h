#ifndef ENTITY_H_
#define ENTITY_H_

#include "Object.h"
#include "MeshData.h"

#include <boost/unordered_set.hpp>

class Component;

class Entity : public Object
{
private:
	boost::unordered_set<boost::container::string> tags;

	boost::container::vector<Component*> components;

	// Scene and component stuff goes here
public:
	Entity();
	Entity(const Transform& t, Entity* parentEntity = nullptr);
	~Entity();

	void Destroy() override;

	// <TAGS>

	inline boost::unordered_set<boost::container::string> GetTags() const { return tags; }
	inline bool HasTag(boost::container::string tag) const { return tags.count(tag) >= 0; }

	// Will probably move tag system purely into script-side once that's up-and-running
	void AddTag(boost::container::string tag);
	void RemoveTag(boost::container::string tag);
	void AddTags(boost::unordered_set<boost::container::string> newTags);

	// Shared pointer for mesh data
	boost::shared_ptr<MeshData> mData;

	void SetMesh();

	// </TAGS>

	// <COMPONENTS>

	inline boost::container::vector<Component*> GetComponents() const { return components; }
	// TODO : Would like to query specific components by type and name

	// </COMPONENTS>

	// Scene and component stuff goes here
};

#endif
