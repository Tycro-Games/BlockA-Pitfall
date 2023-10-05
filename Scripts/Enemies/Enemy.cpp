#include "precomp.h"
#include "Enemy.h"


Subject* Enemy::GetSubject() const
{
	return subject;
}

const float2& Enemy::GetPosition() const
{
	return position;
}

void Enemy::TryToHitPlayer(float distanceToPlayer)
{

	if (length(avatar->GetCollisionChecker()->GetBoxColliderPos() - position) < distanceToPlayer)//hit event
	{
		subject->Notify(damage, PLAYER_HIT);
	}


}

void Enemy::SetPosition(const float2& pos)
{
	position = pos;
}

void Enemy::SetDamage(uint dg)
{
	damage = dg;
}

void Enemy::GetDrawCoordinates()
{
	x1 = static_cast<int>(col.min.x - Camera::GetPosition().x);
	x2 = static_cast<int>(col.max.x - Camera::GetPosition().x);

	y1 = static_cast<int>(col.min.y - Camera::GetPosition().y);
	y2 = static_cast<int>(col.max.y - Camera::GetPosition().y);
}
void Enemy::GetDrawCoordinatesMoving()
{
	x1 = static_cast<int>(position.x + col.min.x - Camera::GetPosition().x);
	x2 = static_cast<int>(position.x + col.max.x - Camera::GetPosition().x);

	y1 = static_cast<int>(position.y + col.min.y - Camera::GetPosition().y);
	y2 = static_cast<int>(position.y + col.max.y - Camera::GetPosition().y);
}
