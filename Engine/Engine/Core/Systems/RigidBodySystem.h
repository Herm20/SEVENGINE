#ifndef RIGID_BODY_SYSTEM_H
#define RIGID_BODY_SYSTEM_H

#include "../ECS/System.h"

class RigidBodySystem : public ecs::System {

public:

	explicit RigidBodySystem(ecs::Manager& manager);

	virtual void startFrame(float dt) override;
	virtual void updateEntity(float dt, ecs::Entity entity) override;
	virtual void endFrame(float dt) override;

};

#endif // !RIGID_BODY_SYSTEM_H
