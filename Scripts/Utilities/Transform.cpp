#include "precomp.h"
#include "Transform.h"

Transform::Transform() : parent(nullptr), pos(nullptr)
{
}

void Transform::ToWorldPos() const
{
	*pos = parent->GetPosition();
}

float2 Transform::GetPosition() const
{
	return *pos;
}
void Transform::SetParent(Transform& _parent)
{
	parent = &_parent;
	*pos = *_parent.pos - *pos;

}


void Transform::SetPointerPos(float2& _pos)
{
	pos = &_pos;

}

void Transform::SetPos(float2 _pos)
{
	*pos = _pos;
}

Transform* Transform::GetParent()
{
	return parent;
}

Transform::~Transform()
= default;
