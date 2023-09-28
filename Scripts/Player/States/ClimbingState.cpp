#include "precomp.h"
#include "ClimbingState.h"


void ClimbingState::OnEnter(Avatar& _p)
{
	cout << "climbing'\n";
	p = &_p;
	p->SetVelocityY(0);
}

PlayerState* ClimbingState::Update(float deltaTime)
{
	const Box floorCollider = p->GetFloorCollider();
	const Box boxCollider = p->GetBoxCollider();
	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!p->IsCollidingFloors(floorCollider) &&
			!p->IsCollidingFloors(boxCollider)) {
			p->SetVelocityY(-CLIMBING_JUMP_FORCE);
			p->ResetClimbTimer();
			p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x));
			return new FreemovingState();
		}
	}


	const float newPosY = (p->GetVelocity().y + static_cast<float>(p->GetInput().arrowKeys.y)) * p->GetSpeed() * deltaTime;


	float2 newPos = p->GetPos() + float2{ 0, newPosY };
	if (p->IsCollidingLadders(newPos, boxCollider)) {
		if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
		{
			p->SetPosition(newPos);
		}
	}
	else if (!p->IsCollidingFloors(newPos, boxCollider)) {
		if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
		{
			p->SetPosition(newPos);
		}
	}
	if (!p->IsCollidingLadders(boxCollider))
	{
		//this is the end of a rope
		float2 floorPos = { 0 };

		if (p->IsCollidingFloors(floorPos, floorCollider)) {
			floorPos.y = floorPos.y - boxCollider.max.y / 2 - floorCollider.max.y / 2;
			p->SetPositionY(floorPos.y);
			p->SetVelocityY(0);

		}
		return new FreemovingState();
	}
	return nullptr;
}

void ClimbingState::OnExit()
{
}

