#include "Object.h"

#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
void Object::RequireUpdate()
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
#endif

void Object::AddChild(Object* newChild)
{
	children.push_back(newChild);
}

void Object::RemoveChild(Object* child)
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

Object::Object() :
	children(),
	parent(nullptr),
	world(identity<mat4>()),
	invWorld(identity<mat4>()),
	worldRotation(identity<quat>()),
	local()
#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
	,needsUpdated(false),
	needsInverseUpdated(false),
	needsRotationUpdated(false)
#endif
{
	// Nothing interesting to do here
}

Object::Object(const Transform& t, Object* parentObject) :
	children(),
	parent(parentObject),
	world(identity<mat4>()),
	invWorld(identity<mat4>()),
	worldRotation(identity<quat>()),
	local(t)
#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE
	,needsUpdated(true),
	needsInverseUpdated(true),
	needsRotationUpdated(true)
#endif
{
	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

Object::~Object()
{
	// Nothing interesting to do here
}

void Object::SetParent(Object* newParent, bool keepWorldTransform)
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

#ifndef CORE_OBJECT_NO_DYNAMIC_UPDATE

vec3 Object::GetWorldPosition()
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

quat Object::GetWorldRotation()
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

mat4 Object::GetWorldMatrix()
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

mat4 Object::GetInverseMatrix()
{
	if (needsInverseUpdated)
	{
		invWorld = inverse(GetWorldMatrix());
		needsInverseUpdated = false;
	}

	return invWorld;
}

#else

void Object::UpdateTransformationsRoot()
{
	world = local.GetMatrix();
	invWorld = inverse(world);
	worldRotation = local.GetRotation();
	worldPosition = local.GetPosition();
}

void Object::UpdateTransformationsChild()
{
	world = parent->world * local.GetMatrix();
	invWorld = inverse(world);
	worldRotation = cross(parent->worldRotation, local.GetRotation());
	worldPosition = parent->world * vec4(local.GetPosition(), 1.0f);
}

#endif

void Object::SetPosition(vec3 v)
{
	local.SetPosition(v);

	RequireUpdate();
}

void Object::SetPositionLocal(vec3 v)
{
	local.SetPosition(rotate(local.GetRotation(), v));

	RequireUpdate();
}

void Object::SetPositionWorld(vec3 v)
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

void Object::SetRotation(quat q)
{
	local.SetRotation(q);

	RequireUpdate();
}

void Object::SetRotationWorld(quat q)
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

void Object::SetScale(vec3 v)
{
	local.SetScale(v);

	RequireUpdate();
}

void Object::Translate(vec3 v)
{
	local.TranslateGlobal(v);

	RequireUpdate();
}

void Object::TranslateLocal(vec3 v)
{
	local.TranslateLocal(v);

	RequireUpdate();
}

void Object::TranslateWorld(vec3 v)
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

void Object::Rotate(quat q)
{
	local.RotateGlobal(q);

	RequireUpdate();
}

void Object::RotateLocal(quat q)
{
	local.RotateLocal(q);

	RequireUpdate();
}

void Object::RotateWorld(quat q)
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

void Object::Scale(vec3 v)
{
	local.ScaleMul(v);

	RequireUpdate();
}

void Object::ScaleAdd(vec3 v)
{
	local.ScaleAdd(v);

	RequireUpdate();
}

void Object::OrbitAboutParent(quat q)
{
	local.SetPosition(rotate(q, local.GetPosition()));
	RequireUpdate();
}

void Object::OrbitAboutWorld(quat q)
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

void Object::OrbitAboutObject(Object* o, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
	}
	else
	{
		local.SetPosition(vec3(o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
	}

	RequireUpdate();
}

void Object::OrbitAboutPoint(vec3 v, quat q)
{
	vec3 offset = rotate(local.GetRotation(), v);
	local.SetPosition(rotate(q, local.GetPosition() - offset) + offset);

	RequireUpdate();
}

void Object::OrbitAboutPointParent(vec3 v, quat q)
{
	local.SetPosition(rotate(q, local.GetPosition() - v) + v);
	RequireUpdate();
}

void Object::OrbitAboutPointWorld(vec3 v, quat q)
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

void Object::OrbitAboutPointObject(Object* o, vec3 v, quat q)
{
	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
	}
	else
	{
		local.SetPosition(vec3(o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
	}

	RequireUpdate();
}

void Object::RevolveAboutParent(quat q)
{
	local.SetPosition(rotate(q, local.GetPosition()));
	local.RotateGlobal(q);
	
	RequireUpdate();
}

void Object::RevolveAboutWorld(quat q)
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

void Object::RevolveAboutObject(Object* o, quat q)
{
	quat eRot = o->GetWorldRotation();

	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(GetWorldRotation(), cross(cross(q, eRot), conjugate(eRot)))));
	}
	else
	{
		local.SetPosition(vec3(o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f))), 1.0f)));
		local.RotateGlobal(cross(conjugate(eRot), cross(q, eRot)));
	}

	RequireUpdate();
}

void Object::RevolveAboutPoint(vec3 v, quat q)
{
	vec3 offset = rotate(local.GetRotation(), v);

	local.SetPosition(rotate(q, local.GetPosition() - offset) + offset);
	local.RotateLocal(q);

	RequireUpdate();
}

void Object::RevolveAboutPointParent(vec3 v, quat q)
{
	local.SetPosition(rotate(q, local.GetPosition() - v) + v);
	local.RotateGlobal(q);

	RequireUpdate();
}

void Object::RevolveAboutPointWorld(vec3 v, quat q)
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

void Object::RevolveAboutPointObject(Object* o, vec3 v, quat q)
{
	quat eRot = o->GetWorldRotation();

	if (parent != nullptr)
	{
		local.SetPosition(vec3(parent->GetInverseMatrix() * o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * parent->GetWorldMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
		local.SetRotation(cross(conjugate(parent->GetWorldRotation()), cross(GetWorldRotation(), cross(cross(q, eRot), conjugate(eRot)))));
	}
	else
	{
		local.SetPosition(vec3(o->GetWorldMatrix() * vec4(rotate(q, vec3(o->GetInverseMatrix() * vec4(local.GetPosition(), 1.0f)) - v) + v, 1.0f)));
		local.RotateGlobal(cross(conjugate(eRot), cross(q, eRot)));
	}

	RequireUpdate();
}
