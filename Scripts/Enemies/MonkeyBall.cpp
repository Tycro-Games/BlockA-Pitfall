#include "precomp.h"
#include "MonkeyBall.h"


void MonkeyBall::UpdatePosition()
{
}

MonkeyBall::MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos)
{
	t = 0;
	subject = s;
	avatar = p;
	monkey = _monkey;
	startPos = _startPos;

	finalPos = p->GetCollisionChecker()->GetBoxColliderPos();
	finalPos.y = startPos.y;
	midPos = lerp(startPos, finalPos, 0.5f + Rand(0.2f)) + float2{ 0,MID_POINT_MIN + MID_POINT_RANDOM * RandomFloat() };

	position = startPos;
	SetDamage(DG);
	col = Box{ -DISTANCE_TO_PLAYER,DISTANCE_TO_PLAYER };
}

MonkeyBall::~MonkeyBall()
{
}



//TODO add on screen
void MonkeyBall::Render(Surface* screen)
{
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, YELLOW);
}

void MonkeyBall::Update(float deltaTime)
{
	t += deltaTime * SPEED;


	position = MathLibrary::QuadraticBezierCurve(startPos, midPos, finalPos, t / timeToReach);


	if (TryToHitPlayer(DISTANCE_TO_PLAYER) ||
		avatar->GetCollisionChecker()->IsCollidingFloors(position, &col))

	{
		monkey->SetBall(nullptr);
		delete this;

	}
}

float MonkeyBall::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}
