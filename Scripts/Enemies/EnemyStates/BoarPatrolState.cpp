#include "precomp.h"
#include "BoarPatrolState.h"


void BoarPatrolState::OnEnter()
{
	originalPos = -1;
	desiredPos = -1;
	t = 0;
}

BoarState* BoarPatrolState::Update(Boar* boar, float deltaTime)
{
	if (originalPos.x < 0) {
		originalPos = boar->GetPosition();
		desiredPos = boar->GetDesiredPos();
	}
	t += deltaTime * SPEED;
	boar->SetPosition(lerp(originalPos, desiredPos, t));
	if (t > 1)
	{
		boar->SetDesiredPos(originalPos);
		OnEnter();

	}
	return nullptr;
}

void BoarPatrolState::OnExit()
{
}
