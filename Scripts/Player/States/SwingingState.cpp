#include "precomp.h"
#include "SwingingState.h"

void SwingingState::OnEnter(Avatar& _p)
{
	cout << "swinging'\n";
	p = &_p;
}

PlayerState* SwingingState::Update(float deltaTime)
{
	const Box floorCollider = p->GetFloorCollider();
	const Box boxCollider = p->GetBoxCollider();
	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!p->IsCollidingFloors(floorCollider) &&
			!p->IsCollidingFloors(boxCollider)) {
			p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x) * SWINGING_JUMP_SPEED);
			p->SetVelocityY(-SWINGING_JUMP_SPEED);
			p->ResetClimbTimer();

			return new FreemovingState();
		}
	}
	p->SetVelocityX(-(p->GetPos().x - ropePoint->x + p->GetBoxColliderOffset().x));
	p->SetPosition(*ropePoint - p->GetBoxColliderOffset());
	return nullptr;
}

void SwingingState::OnExit()
{
}



void SwingingState::pSetRope(float2* _pRopePoints)
{
	ropePoint = _pRopePoints;
}
