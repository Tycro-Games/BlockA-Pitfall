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
	InitSeed(headingRight);
	timeToTurn += RandomFloat()*RANDOM_MODIFIER_TIME ;
}

MonkeyState* MonkeyTurnState::Update(Monkey* monkey, float deltaTime)
{
	if (stopTimer->elapsed() > timeToTurn)
	{
		MonkeyPatrolState* patrolState = new MonkeyPatrolState();
		//to the other direction
		patrolState->SetHeading(!headingRight);
		patrolState->SetOriginalPosition(monkey->GetPosition());
		const float clampedFloat = clamp(MIN_VALUE, 1.0f, RandomFloat());
		patrolState->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(clampedFloat, !headingRight));
		return patrolState;
	}
	return nullptr;
}

void MonkeyTurnState::OnExit()
{
}

void MonkeyTurnState::SetHeading(bool _heading)
{
	headingRight = _heading;
}
