#include "precomp.h"
#include "MonkeyBall.h"


void MonkeyBall::UpdateVelocity()
{
	dir.x = KinematicEquation(0, velocity.x, sPos.x, t);
	dir.y = KinematicEquation(speed, velocity.y, sPos.y, t);
}

MonkeyBall::MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos)
{
	subject = s;
	avatar = p;
	sPos = _startPos;
	monkey = _monkey;
	fPos = p->GetCollisionChecker()->GetBoxColliderPos();
	fPos.y = fPos.y - 15;
	position = sPos;
	speed = GetVelocity(sPos.x, fPos.y, timeToReach);
	velocity = normalize(fPos - sPos) * speed;
	SetDamage(DG);
	col = Box{ -DISTANCE_TO_PLAYER,DISTANCE_TO_PLAYER };
}

MonkeyBall::~MonkeyBall()
{

}

//derived from https://youtu.be/3lBYVSplAuo?si=8QG2rB5ZFNHWYubu&t=173
float MonkeyBall::KinematicEquation(float a, float v, float p, float _t)
{
	return a * _t * _t * 0.5f + v * _t + p;
}
float MonkeyBall::GetVelocity(float pI, float pF, float t)
{
	return (pF - pI) / t;
}
//TODO add on screen
void MonkeyBall::Render(Surface* screen)
{
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, YELLOW);
}

void MonkeyBall::Update(float deltaTime)
{
	t += deltaTime;
	UpdateVelocity();
	position = dir;

	if (TryToHitPlayer(DISTANCE_TO_PLAYER))
	{
		monkey->SetBall(nullptr);
		delete this;

	}
}

float MonkeyBall::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}
