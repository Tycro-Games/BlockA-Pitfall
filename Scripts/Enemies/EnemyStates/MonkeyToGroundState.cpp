#include "precomp.h"
#include "MonkeyToGroundState.h"

#include "MonkeyPatrolState.h"

void MonkeyToGroundState::OnEnter()
{
}

void MonkeyToGroundState::OnExit()
{
}

MonkeyToGroundState::~MonkeyToGroundState()
{
}

MonkeyState* MonkeyToGroundState::Update(Monkey* monkey, float deltaTime)
{
	float newPosY = 0;
	float2 oldPosition = monkey->GetPosition();
	Box* col = monkey->GetBox();

	if (!monkey->GetCollisionChecker()->IsCollidingFloors(oldPosition, col))
	{
		cout << "Do not go there monkey'\n";
		newPosY += deltaTime * FALL_SPEED;
	}
	else
	{
		MonkeyPatrolState* patrol = new MonkeyPatrolState();
		patrol->SetOriginalPosition(monkey->GetPosition());
		patrol->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(RandomFloat()));
		return patrol;
	}
	monkey->SetPosition(float2{ oldPosition .x,oldPosition.y+newPosY });
	return nullptr;
}
