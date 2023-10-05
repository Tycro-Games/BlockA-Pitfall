#include "precomp.h"
#include "BoarPatrolState.h"


void BoarPatrolState::OnEnter()
{
	originalPos = -1;
	desiredPos = -1;
	t = 0;
}

BoarState* BoarPatrolState::TurnBack(Boar* boar) const
{
	boar->SwitchPositions();
	BoarTurnState* turnState = new BoarTurnState();
	turnState->SetHeading(GetHeading());
	turnState->SetOriginalPos(desiredPos);
	return turnState;
}

float BoarPatrolState::GetHeading() const
{

	if (desiredPos.x - originalPos.x > 0)
		return 1.0f;

	return  -1.0f;

}

BoarState* BoarPatrolState::Update(Boar* boar, float deltaTime)
{
	if (originalPos.x < 0) {
		originalPos = boar->GetPosition();
		desiredPos = boar->GetEndPos();
		t = invlerp(boar->GetStartPos().x, boar->GetEndPos().x, originalPos.x);
	}
	if (boar->IsOnScreen()) {
		if (boar->AtackPlayer() && boar->GetHitTimer()->elapsed() > STOP_DELAY) {
			boar->GetHitTimer()->reset();
			BoarStopState* stopState = new BoarStopState();
			stopState->SetHeading(GetHeading());
			stopState->SetOriginalPos(boar->GetPosition());
			return stopState;
		}
	}

	t += deltaTime * SPEED;
	boar->SetPosition(lerp(boar->GetStartPos(), desiredPos, t));
	if (t > 1)
	{

		return TurnBack(boar);

	}
	return nullptr;
}

void BoarPatrolState::OnExit()
{
}
