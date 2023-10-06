#include "precomp.h"
#include "MonkeyThrowState.h"

MonkeyThrowState::~MonkeyThrowState()
{
}

void MonkeyThrowState::OnEnter()
{
	stopTimer = new Timer();



}

MonkeyState* MonkeyThrowState::Update(Monkey* monkey, float deltaTime)
{
	if (stopTimer->elapsed() > TIME_TO_THROW )
	{
		cout << "Thorws some stuff'\n";
		monkey->GetThrowTimer()->reset();
		MonkeyPatrolState* patrolState = new MonkeyPatrolState();
		patrolState->SetOriginalPosition(monkey->GetPosition());
		const float clampedFloat = clamp(MIN_VALUE, 1.0f, RandomFloat());
		patrolState->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(clampedFloat, !monkey->GetHeading()));
		return patrolState;
	}
	return nullptr;

}

void MonkeyThrowState::OnExit()
{

}
