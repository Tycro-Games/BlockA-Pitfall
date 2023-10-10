#include "precomp.h"
#include "MonkeyToGroundState.h"

void MonkeyToGroundState::OnEnter()
{
	InitSeed(RandomUInt());

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
	if(monkey->GetCollisionChecker()->IsCollidingLadders(oldPosition, col))
	{
		return new MonkeyOnLadderState();
	}
	if (!monkey->GetCollisionChecker()->IsCollidingFloors(oldPosition, col))
	{
		newPosY += deltaTime * FALL_SPEED;
	}
	else
	{
		MonkeyPatrolState* patrol = new MonkeyPatrolState();
		patrol->SetOriginalPosition(monkey->GetPosition());
		patrol->SetDesiredPosition(Monkey::GetValueFromMonkeyFunction(RandomFloat(), true));
		return patrol;
	}
	monkey->SetPosition(float2{ oldPosition .x,oldPosition.y+newPosY });
	return nullptr;
}
