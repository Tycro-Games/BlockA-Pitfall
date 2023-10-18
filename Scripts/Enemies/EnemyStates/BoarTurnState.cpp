#include "precomp.h"
#include "BoarTurnState.h"

void BoarTurnState::OnEnter()
{
	t = 0;
	heading *= turnAmount;
	desiredPos = float2{originalPos.x + heading, originalPos.y};
}

void BoarTurnState::OnExit()
{
}

void BoarTurnState::SetHeading(float _heading)
{
	heading = _heading;
}

void BoarTurnState::SetOriginalPos(const float2& _originalPos)
{
	originalPos = _originalPos;
}

BoarState* BoarTurnState::Update(Boar* boar, float deltaTime)
{
	t += deltaTime * SPEED;
	boar->SetPosition(lerp(originalPos, desiredPos, sinf(t)));
	if (t > PI)
		return new BoarPatrolState();
	return nullptr;
}
