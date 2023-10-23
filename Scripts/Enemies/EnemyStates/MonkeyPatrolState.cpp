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
	const float2 touchFloor = {0, monkey->GetDistanceToPlayer() * 2};
	if (monkey->IsOnScreen())
	{
		if (monkey->SeesPlayer() && monkey->GetThrowTimer()->elapsedF() > THROW_COOLDOWN)
		{
			return new MonkeyThrowState();
		}

		if (monkey->TryToHitPlayer(monkey->GetDistanceToPlayer()) && monkey->GetHitTimer()->elapsedF() >
			HIT_TIME_COOLDOWN)
		{
			monkey->GetHitTimer()->reset();
			//add throw
			return ToTurnState();
		}
	}
	if (monkey->GetCollisionChecker()->IsCollidingFloorsAllCorners(newPos + touchFloor, monkey->GetBox()))
	{
		monkey->SetPosition(newPos);
		if (t > 1) //reached destination
		{
			return ToTurnState();
		}
	}
	else
	{
		return ToTurnState();
	}
	return nullptr;
}

void MonkeyPatrolState::OnExit()
{
}

void MonkeyPatrolState::SetDesiredPosition(float x)
{
	currentOffset = x * DISTANCE_TO_NEXT_POSITION + MIN_TO_NEXT_POSITION * MathLibrary::Sign(x);
	desiredPos = float2{originalPosition.x + currentOffset, originalPosition.y};
}

void MonkeyPatrolState::SetOriginalPosition(const float2& pos)
{
	originalPosition = pos;
}
