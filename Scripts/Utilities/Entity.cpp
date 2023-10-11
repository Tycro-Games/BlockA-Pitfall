#include "precomp.h"
#include "Entity.h"

void Entity::SetActive(bool val)
{
	isActive = val;
}

bool Entity::GetActive() const
{
	return isActive;
}
