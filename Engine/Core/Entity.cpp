#include "Entity.h"

#include "Game.h"

Entity::Entity() :
	children(),
	parent(nullptr),
	tags(),
	world(identity<mat4>()),
	invWorld(identity<mat4>()),
	worldRotation(identity<quat>()),
	local(),
	needsUpdated(false),
	needsInverseUpdated(false),
	needsRotationUpdated(false)
{
	// Nothing interesting to do here
}

Entity::Entity(const Transform& t, Entity* parentEntity) :
	children(),
	parent(parentEntity),
	tags(),
	world(identity<mat4>()),
	invWorld(identity<mat4>()),
	worldRotation(identity<quat>()),
	local(t),
	needsUpdated(true),
	needsInverseUpdated(true),
	needsRotationUpdated(true)
{
	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

Entity::~Entity()
{
	// Nothing interesting to do here
}

void Entity::AddChild(Entity* newChild)
{
	children.push_back(newChild);
}

void Entity::RemoveChild(Entity* child)
{
	// Because order doesn't matter, we can zip through and pop it out quickly
	u64 cc = children.size();
	for (u64 i = 0; i < cc; ++i)
	{
		if (children[i] == child)
		{
			children[i] = children[cc - 1];
			children.pop_back();
			return;
		}
	}
}

void Entity::RequireUpdate()
{
	needsUpdated = true;
	needsInverseUpdated = true;
	needsRotationUpdated = true;

	// Recursively require updates in all children, as a change in this affects them
	u64 cc = children.size();
	for (u64 i = 0; i < cc; ++i)
	{
		children[i]->RequireUpdate();
	}
}

void Entity::Destroy()
{
	// TODO : Scene and component cleanup

	u64 cc = children.size();
	for (u64 i = 0; i < cc; ++i)
	{
		children[0]->Destroy();
	}

	if (parent != nullptr)
	{
		parent->RemoveChild(this);
	}
}

void Entity::SetParent(Entity* newParent, bool keepWorldTransform)
{
	vec3 curPos = GetWorldPosition();
	quat curRot = GetWorldRotation();

	if (parent) { parent->RemoveChild(this); }
	if (newParent) { newParent->AddChild(this); }
	parent = newParent;

	if (keepWorldTransform)
	{
		SetPositionWorld(curPos);
		SetRotationWorld(curRot);
	}

	RequireUpdate();
}

void Entity::AddTag(std::string tag)
{
	// TODO : Add logic for interfacing scene - various tag optimizations
	tags.push_back(tag);
}

void Entity::RemoveTag(std::string tag)
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

// TODO : Component and scene stuff goes here

vec3 Entity::GetWorldPosition()
{
	if (parent != nullptr)
	{
		return vec3(parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f));
	}
	else
	{
		return local.GetPosition();
	}
}

quat Entity::GetWorldRotation()
{
	if (needsRotationUpdated)
	{
		quat worldRot = local.GetRotation();

		if (parent)
		{
			worldRot = cross(parent->GetWorldRotation(), worldRot);
		}

		worldRotation = worldRot;
		needsRotationUpdated = false;
	}

	return worldRotation;
}

mat4 Entity::GetWorldMatrix()
{
	if (needsUpdated)
	{
		if (parent != nullptr)
		{
			world = parent->GetWorldMatrix() * local.GetMatrix();
		}
		else
		{
			world = local.GetMatrix();
		}

		needsUpdated = false;
	}

	return world;
}

mat4 Entity::GetInverseMatrix()
{
	if (needsInverseUpdated)
	{
		invWorld = inverse(GetWorldMatrix());
		needsInverseUpdated = false;
	}

	return invWorld;
}

void Entity::SetPosition(vec3 v)
{
	local.SetPosition(v);

	RequireUpdate();
}

void Entity::SetPositionLocal(vec3 v)
{
	local.SetPosition(rotate(local.GetRotation(), v));

	RequireUpdate();
}

void Entity::SetPositionWorld(vec3 v)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * vec4(v, 1.0f)));
	}
	else
	{
		local.SetPosition(v);
	}

	RequireUpdate();
}

void Entity::SetRotation(quat q)
{
	local.SetRotation(q);

	RequireUpdate();
}

void Entity::SetRotationWorld(quat q)
{
	if (parent != nullptr)
	{
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), q));
	}
	else
	{
		local.SetRotation(q);
	}

	RequireUpdate();
}

void Entity::SetScale(vec3 v)
{
	local.SetScale(v);

	RequireUpdate();
}

void Entity::Translate(vec3 v)
{
	local.TranslateGlobal(v);

	RequireUpdate();
}

void Entity::TranslateLocal(vec3 v)
{
	local.TranslateLocal(v);

	RequireUpdate();
}

void Entity::TranslateWorld(vec3 v)
{
	if (parent != nullptr)
	{
		local.TranslateGlobal(vec3(parent->GetInverseMatrix() * (parent->GetWorldMatrix() * vec4(v, 1.0f))));
	}
	else
	{
		local.TranslateGlobal(v);
	}

	RequireUpdate();
}

void Entity::Rotate(quat q)
{
	local.RotateGlobal(q);

	RequireUpdate();
}

void Entity::RotateLocal(quat q)
{
	local.RotateLocal(q);

	RequireUpdate();
}

void Entity::RotateWorld(quat q)
{
	if (parent != nullptr)
	{
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(q, GetWorldRotation())));
	}
	else
	{
		local.RotateGlobal(q);
	}

	RequireUpdate();
}

void Entity::Scale(vec3 v)
{
	local.ScaleMul(v);

	RequireUpdate();
}

void Entity::ScaleAdd(vec3 v)
{
	local.ScaleAdd(v);

	RequireUpdate();
}

void Entity::OrbitAboutParent(quat q)
{
	local.SetPosition(rotate(q, local.GetPosition()));
	RequireUpdate();
}

void Entity::OrbitAboutWorld(quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * vec4(rotate(q, vec3(parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
	}
	else
	{
		local.SetPosition(rotate(q, local.GetPosition()));
	}

	RequireUpdate();
}

void Entity::OrbitAboutEntity(Entity* e, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
	}
	else
	{
		local.SetPosition(vec3(e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
	}

	RequireUpdate();
}

void Entity::OrbitAboutPoint(vec3 v, quat q)
{
	vec3 offset = rotate(local.GetRotation(), v);
	local.SetPosition(rotate(q, local.GetPosition() - offset) + offset);

	RequireUpdate();
}

void Entity::OrbitAboutPointParent(vec3 v, quat q)
{
	local.SetPosition(rotate(q, local.GetPosition() - v) + v);
	RequireUpdate();
}

void Entity::OrbitAboutPointWorld(vec3 v, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * vec4(rotate(q, vec3(parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
	}
	else
	{
		local.SetPosition(rotate(q, local.GetPosition() - v) + v);
	}

	RequireUpdate();
}

void Entity::OrbitAboutPointEntity(Entity* e, vec3 v, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
	}
	else
	{
		local.SetPosition(vec3(e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
	}

	RequireUpdate();
}

void Entity::RotateAboutParent(quat q)
{
	local.SetPosition(rotate(q, local.GetPosition()));
	local.RotateGlobal(q);
	
	RequireUpdate();
}

void Entity::RotateAboutWorld(quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * vec4(rotate(q, vec3(parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(q, GetWorldRotation())));
	}
	else
	{
		// Copied from RotateAboutParent (not trusting the compiler to inline that)
		local.SetPosition(rotate(q, local.GetPosition()));
		local.RotateGlobal(q);
	}

	RequireUpdate();
}

void Entity::RotateAboutEntity(Entity* e, quat q)
{
	quat eRot = e->GetWorldRotation();

	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(GetWorldRotation(), cross(cross(q, eRot), conjugate(eRot)))));
	}
	else
	{
		local.SetPosition(vec3(e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
		local.RotateGlobal(cross(conjugate(eRot), cross(q, eRot)));
	}

	RequireUpdate();
}

void Entity::RotateAboutPoint(vec3 v, quat q)
{
	vec3 offset = rotate(local.GetRotation(), v);

	local.SetPosition(rotate(q, local.GetPosition() - offset) + offset);
	local.RotateLocal(q);

	RequireUpdate();
}

void Entity::RotateAboutPointParent(vec3 v, quat q)
{
	local.SetPosition(rotate(q, local.GetPosition() - v) + v);
	local.RotateGlobal(q);

	RequireUpdate();
}

void Entity::RotateAboutPointWorld(vec3 v, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * vec4(rotate(q, vec3(parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(q, GetWorldRotation())));
	}
	else
	{
		// Copied from RotateAboutPointParent (not trusting the compiler to inline that)
		local.SetPosition(rotate(q, local.GetPosition() - v) + v);
		local.RotateGlobal(q);
	}

	RequireUpdate();
}

void Entity::RotateAboutPointEntity(Entity* e, vec3 v, quat q)
{
	quat eRot = e->GetWorldRotation();

	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(GetWorldRotation(), cross(cross(q, eRot), conjugate(eRot)))));
	}
	else
	{
		local.SetPosition(vec3(e->GetWorldMatrix() * vec4(rotate(q, vec3(e->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
		local.RotateGlobal(cross(conjugate(eRot), cross(q, eRot)));
	}

	RequireUpdate();
}