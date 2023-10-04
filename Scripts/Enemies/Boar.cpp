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
	if(onScreen)
		TryToHitPlayer(DISTANCE_TO_PLAYER);

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
	delete currentState;
	delete subject;
}

void Boar::Init(const float2& _a, const float2& _b, Avatar& _avatar)
{
	subject = new Subject();

	avatar = &_avatar;
	pointA = _a;
	pointB = _b;
	currentState = new BoarPatrolState();
	position = pointA;
	desiredPos = pointB;

	col = Box{ -DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER };
	SetDamage(DAMAGE);

}

const float2& Boar::GetDesiredPos() const
{
	return desiredPos;
}

void Boar::SetDesiredPos(const float2& _desiredPos)
{
	desiredPos = _desiredPos;
}

float Boar::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}


