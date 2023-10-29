#include "precomp.h"
#include "MonkeyBall.h"


MonkeyBall::MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos, const float2& _midPos,
                       const float2& _finalPos, float _speed)
{
	delete subject;
	t = 0;
	subject = s;
	avatar = p;
	monkey = _monkey;
	startPos = _startPos;
	speed = _speed;
	finalPos = _finalPos;
	midPos = _midPos;

	sprite = new Sprite(new Surface("assets/rock_16x16.png"), 1);


	position = startPos;
	SetDamage(DG);
	col = Box{-DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER};
}

MonkeyBall::~MonkeyBall()
{
	subject = nullptr;
	delete sprite;
}


//TODO add on screen
void MonkeyBall::Render(Surface* screen)
{
	GetDrawCoordinatesMoving();
#ifdef _DEBUG
	screen->Box(x1, y1, x2, y2, YELLOW);
#endif
	sprite->Draw(screen, x1, y1);
}

void MonkeyBall::Update(float deltaTime)
{
	//code behind the projectile the monkey throw
	t += deltaTime * speed;

	position = MathLibrary::QuadraticBezierCurve(startPos,
	                                             midPos,
	                                             finalPos,
	                                             t / timeToReach);


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
