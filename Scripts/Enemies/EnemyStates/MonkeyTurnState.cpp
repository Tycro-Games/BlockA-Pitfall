#include "precomp.h"
#include "MonkeyTurnState.h"

#include "MonkeyPatrolState.h"

MonkeyTurnState::~MonkeyTurnState()
{
	delete stopTimer;

}

void MonkeyTurnState::OnEnter()
{
	stopTimer = new Timer();
	
	timeToTurn += RandomFloat()*RANDOM_MODIFIER_TIME ;
}

MonkeyState* MonkeyTurnState::Update(Monkey* monkey, float deltaTime)
{
	if (stopTimer->elapsed() > timeToTurn)
	{
		MonkeyPatrolState* patrolState = new MonkeyPatrolState();
		//to the other direction
		monkey->SetHeading(!monkey->GetHeading());
		patrolState->SetOriginalPosition(monkey->GetPosition());
		const float clampedFloat = clamp(MIN_VALUE, 1.0f, RandomFloat());
		patrolState->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(clampedFloat, !monkey->GetHeading()));
		return patrolState;
	}
	return nullptr;
}

void MonkeyTurnState::OnExit()
{
}

