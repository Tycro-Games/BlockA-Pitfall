#include "precomp.h"
#include "Enemy.h"


Subject* Enemy::GetSubject() const
{
	return subject;
}

float2 Enemy::GetPosition() const
{
	return position;
}
