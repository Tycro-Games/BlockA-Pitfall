#include "precomp.h"
#include "Enemy.h"


Enemy::~Enemy()
{
	delete hp;
}

Enemy::Enemy()
{
	hp = new Health();
}

void Enemy::Update(float deltaTime)
{
	deltaTime;
	if (onScreen)
		DetectHit();
}

Subject* Enemy::GetSubject() const
{
	return subject;
}

const float2& Enemy::GetPosition() const
{
	return position;
}

bool Enemy::TryToHitPlayer(float distanceToPlayer) const
{
	if (length(avatar->GetCollisionChecker()->GetBoxColliderPos() - position) < distanceToPlayer) //hit event
	{
		subject->Notify(damage, PLAYER_HIT);
		return true;
	}
	return false;
}

void Enemy::Dead()
{
	if (hp->IsDead())
	{
		subject->Notify(points, ENEMY_DEAD);
		SetActive(false);
	}
}

void Enemy::HitByPlayer(int _damage)
{
	hp->TakeDamage(_damage);
	Dead();
}

void Enemy::DetectHit()
{
	Array<Rock>& rocks = avatar->GetRocks();
	for (uint i = 0; i < rocks.GetCount(); i++)
	{
		if (!rocks[i].GetActive())
			continue;


		float2 rockPos = rocks[i].GetPosition();
		Box rockBox = rocks[i].GetBoxCollider();
		//AABB check
		if (!AABB::BoxCollides(AABB::At(rockPos, rockBox), AABB::At(position, col)))
			continue;

		Surface* rock = avatar->GetRockSpawner()->GetRockSprite();
		Surface* enemySurface = GetSurface();
		if (enemySurface == nullptr)
			continue;
		float2 camPos = Camera::GetPosition();
		const float2 rP = rockPos - camPos;
		const float2 eP = position - camPos;
		const int2 screenRockPos = {static_cast<int>(rP.x), static_cast<int>(rP.y)};
		const int2 screenEnemyPosition = {static_cast<int>(eP.x), static_cast<int>(eP.y)};
		if (MathLibrary::PixelCollision(rock, enemySurface, screenRockPos, screenEnemyPosition))
		{
			rocks[i].SetActive(false);

			HitByPlayer(10);
		}
	}
}


void Enemy::SetPosition(const float2& pos)
{
	position = pos;
}


void Enemy::SetDamage(int dg)
{
	damage = dg;
}

Box* Enemy::GetBox()
{
	return &col;
}

Avatar* Enemy::GetAvatar() const
{
	return avatar;
}

bool Enemy::IsOnScreen() const
{
	return onScreen;
}

void Enemy::SetPoints(int p)
{
	points = p;
}

void Enemy::SetHP(int _hp) const
{
	hp->SetHp(_hp);
}

Surface* Enemy::GetSurface()
{
	return surface;
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

void Enemy::GetDrawCoordinatesMoving(const Box& _col)
{
	x1 = static_cast<int>(position.x + _col.min.x - Camera::GetPosition().x);
	x2 = static_cast<int>(position.x + _col.max.x - Camera::GetPosition().x);

	y1 = static_cast<int>(position.y + _col.min.y - Camera::GetPosition().y);
	y2 = static_cast<int>(position.y + _col.max.y - Camera::GetPosition().y);
}
