#include "precomp.h"
#include "MonkeyPatrolState.h"

MonkeyPatrolState::~MonkeyPatrolState()
{
}

void MonkeyPatrolState::OnEnter()
{
}

MonkeyState* MonkeyPatrolState::Update(Monkey* monkey, float deltaTime)
{
	t += deltaTime * SPEED_TIME*RandomFloat();
	float2 newPos = lerp(originalPosition, desiredPos, t);
	float2 touchFloor = { 0,10 };
	if (monkey->GetCollisionChecker()->IsCollidingFloorsComplete(newPos + touchFloor, monkey->GetBox())) {



		monkey->SetPosition(newPos);
		if (t > 1)
		{
			originalPosition = desiredPos;
			SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(RandomFloat()));
			t = 0;
		}
	}
	else
	{
		t = 0;

		originalPosition = monkey->GetPosition();
		desiredPos.x = (originalPosition.x - currentOffset);
	}
	return nullptr;
}

void MonkeyPatrolState::OnExit()
{
}

void MonkeyPatrolState::SetDesiredPosition(float x)
{
	currentOffset = x * DISTANCE_TO_NEXT_POSITION;
	desiredPos = float2{ originalPosition.x + currentOffset ,originalPosition.y };
}

void MonkeyPatrolState::SetOriginalPosition(const float2& pos)
{
	originalPosition = pos;
}
