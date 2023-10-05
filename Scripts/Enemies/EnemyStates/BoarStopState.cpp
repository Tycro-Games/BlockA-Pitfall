#include "precomp.h"
#include "BoarStopState.h"

void BoarStopState::OnEnter()
{
	t = 0;

}

BoarState* BoarStopState::Update(Boar* boar, float deltaTime)
{
	t += deltaTime;
	if (t > STOP_TIME) {
		boar->SwitchPositions();
		BoarTurnState* turnState = new BoarTurnState();
		turnState->SetHeading(heading);
		turnState->SetOriginalPos(originalPos);
		return turnState;
	}
	return nullptr;
}

void BoarStopState::OnExit()
{
}

void BoarStopState::SetHeading(float _heading)
{
	heading = _heading;
}

void BoarStopState::SetOriginalPos(const float2& _originalPos)
{
	originalPos = _originalPos;
}
