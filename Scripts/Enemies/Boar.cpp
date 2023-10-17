#include "precomp.h"
#include "Boar.h"

void Boar::Render(Surface* screen)
{
	if (!onScreen)
		return;
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, GREEN);

}

void Boar::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, col);
	
	Enemy::Update(deltaTime);

	BoarState* state = currentState->Update(this, deltaTime);
	if (state != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = state;
		currentState->OnEnter();

	}
}

Boar::~Boar()
{
	delete hitRecently;
	delete currentState;
	delete subject;
}

bool Boar::AtackPlayer()
{
	return TryToHitPlayer(DISTANCE_TO_PLAYER);
}
void Boar::Init(const float2& _a, const float2& _b, Avatar& _avatar)
{
	subject = new Subject();
	hitRecently = new Timer();
	avatar = &_avatar;
	pointA = _a;
	pointB = _b;
	currentState = new BoarPatrolState();
	SetHP(HP);

	position = pointA;
	desiredPos = pointB;
	SetPoints(BOAR_POINTS);
	col = Box{ -DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER };
	SetDamage(DAMAGE);

}

const float2& Boar::GetDesiredPos() const
{
	return desiredPos;
}
const float2& Boar::GetStartPos() const
{
	return pointA;
}
const float2& Boar::GetEndPos() const
{
	return pointB;
}
void Boar::SwitchPositions() 
{
	swap(pointA, pointB);
}

void Boar::SetDesiredPos(const float2& _desiredPos)
{
	desiredPos = _desiredPos;
}

float Boar::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}


Timer* Boar::GetHitTimer() const
{
	return hitRecently;
}


