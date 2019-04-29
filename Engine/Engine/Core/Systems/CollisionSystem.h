#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <glm/glm.hpp>

#include "../ECS/System.h"
#include "ScriptSystem.h"

class CollisionSystem : public ecs::System {

private:

	ScriptSystem* scriptSystem;

public:

	explicit CollisionSystem(ecs::Manager& manager, ScriptSystem* scriptSys);

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

};

#endif // !COLLISION_SYSTEM_H
