#ifndef ENTITY_H_
#define ENTITY_H_

#include "Object.h"
#include "SceneRef.h"
#include "MeshData.h"
#include "ECS/Component.h"

#include <boost/unordered_set.hpp>
#include <unordered_map>
#include <memory>

using namespace ecs;

class Scene;

class Entity : public Object
{
private:
	boost::unordered_set<boost::container::string> tags;
	std::unordered_map<const std::type_info*, Component*> components;
	SceneRef scene;

	// Actually handles internal entity deletion, called by managing scene
	void DestroyInternal();

	friend class Scene;

public:
	Entity();
	Entity(Scene* parentScene, u64 ind, u64 sID, u64 tID, const Transform& t = Transform(), Entity* parentEntity = nullptr);
	~Entity();

	// Flags the entity for deletion
	void Destroy();

	// <TAGS>

	inline boost::unordered_set<boost::container::string> GetTags() const { return tags; }
	inline bool HasTag(boost::container::string tag) const { return tags.count(tag) >= 0; }

	// Will probably move tag system purely into script-side once that's up-and-running
	void AddTag(boost::container::string tag);
	void RemoveTag(boost::container::string tag);
	void AddTags(boost::unordered_set<boost::container::string> newTags);

	// </TAGS>

	// <COMPONENTS>

	//inline std::map<std::type_index, std::shared_ptr<Component>> GetComponents() const { return components; }
	template <typename T>
	T* AddComponent() {
		T* newComponent = new T();
		components[&typeid(*newComponent)] = newComponent;
		return newComponent;
	}

	template <typename T>
	T* GetComponent() {
		if (components.count(&typeid(T)) != 0) {
			return static_cast<T*>(components[&typeid(T)]);
		}
		else {
			return nullptr;
		}
	}

	// </COMPONENTS>

	// Scene and component stuff goes here
};


#endif
