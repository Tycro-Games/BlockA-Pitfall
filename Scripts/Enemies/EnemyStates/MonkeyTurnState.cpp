#include "precomp.h"
#include "MonkeyTurnState.h"

#include "MonkeyPatrolState.h"

MonkeyTurnState::~MonkeyTurnState()
{
	delete stopTimer;

}

void MonkeyTurnState::OnEnter()
{
	
	
}

MonkeyState* MonkeyTurnState::Update(Monkey* monkey, float deltaTime)
{
	if(stopTimer==nullptr)
	{
		stopTimer = new Timer();
		SetSeed(InitSeed(static_cast<uint>(monkey->GetPosition().x)));
		timeToTurn += Rand(RANDOM_MODIFIER_TIME);
	}
	if (stopTimer->elapsed() > timeToTurn)
	{
		MonkeyPatrolState* patrolState = new MonkeyPatrolState();
		//to the other direction
		monkey->SetHeading(!monkey->GetHeading());
		patrolState->SetOriginalPosition(monkey->GetPosition());
		const float clampedFloat = RandomFloat();
		patrolState->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(clampedFloat, !monkey->GetHeading()));
		return patrolState;
	}
	return nullptr;
}

void MonkeyTurnState::OnExit()
{
}

