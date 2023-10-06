#include "precomp.h"
#include "MonkeyPatrolState.h"

#include "MonkeyTurnState.h"

MonkeyPatrolState::~MonkeyPatrolState()
{
}

void MonkeyPatrolState::SetSpeedModifier()
{
	t = 0;

	SPEED_MODIFIER = clamp(MIN_SPEED, 1.0f, RandomFloat());
}

void MonkeyPatrolState::OnEnter()
{

	SetSpeedModifier();
}

MonkeyState* MonkeyPatrolState::ToTurnState() const
{
	MonkeyTurnState* turnState = new MonkeyTurnState();
	return turnState;
}

MonkeyState* MonkeyPatrolState::Update(Monkey* monkey, float deltaTime)
{
	t += deltaTime * SPEED_TIME * SPEED_MODIFIER;
	const float2 newPos = lerp(originalPosition, desiredPos, t);
	const float2 touchFloor = { 0,monkey->GetDistanceToPlayer() * 2 };
	if(monkey->SeesPlayer()&&monkey->GetThrowTimer()->elapsedF() > THROW_COOLDOWN)
	{
		return new MonkeyThrowState();
	}
	if (monkey->TryToHitPlayer(monkey->GetDistanceToPlayer()) && monkey->GetHitTimer()->elapsedF() > HIT_TIME_COOLDOWN) {
		cout << "Player hit'\n";
		monkey->GetHitTimer()->reset();
		//add throw
		//ignore for a few seconds
		return ToTurnState();

	}
	if (monkey->GetCollisionChecker()->IsCollidingFloorsComplete(newPos + touchFloor, monkey->GetBox())) {

		monkey->SetPosition(newPos);
		if (t > 1)
		{

			return ToTurnState();

		}
	}
	else
	{
		/*SetSpeedModifier();
		originalPosition = monkey->GetPosition();
		desiredPos.x = (originalPosition.x - currentOffset);*/
		return ToTurnState();

	}
	return nullptr;
}

void MonkeyPatrolState::OnExit()
{
}

void MonkeyPatrolState::SetDesiredPosition(float x)
{
	float sign = x > 0 ? 1 : -1;
	currentOffset = x * DISTANCE_TO_NEXT_POSITION + MIN_TO_NEXT_POSITION * sign;
	desiredPos = float2{ originalPosition.x + currentOffset ,originalPosition.y };
}

void MonkeyPatrolState::SetOriginalPosition(const float2& pos)
{
	originalPosition = pos;
}

