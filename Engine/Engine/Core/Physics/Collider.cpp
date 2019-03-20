#include "Collider.h"

vec3 Collider::GetScale() const {
	return GetEntity()->GetScale() * size;
}

vec3 Collider::GetPosition() const {
	return GetEntity()->GetPosition();
}

quat Collider::GetRotation() const {
	return GetEntity()->GetRotation();
}