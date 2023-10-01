#include "precomp.h"
#include "SwingingState.h"

void SwingingState::OnEnter(Avatar& _p)
{
	cout << "swinging'\n";
	p = &_p;
	p->SetVelocityX(-(p->GetPos().x + p->GetBoxColliderOffset().x - ropePoint->x + OFFSET_ROPE.x));
	previousR = *ropePoint;
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
	float2 offsetSign = OFFSET_ROPE;
	float2 ropP = *ropePoint;
	//left or right
	float heading = previousR.x - ropP.x;
	if (heading > 0) {
		//player should be on the left in this case
		offsetSign.x *= -1;
	}
	//neccesary for giving the illusion
	//of weight when the player is swinging
	if (abs(heading) < 1.0f)
		offsetSign.x *= abs(heading);
	//player is looking in the right directions
	p->SetVelocityX(-(p->GetPos().x +
		p->GetBoxColliderOffset().x - ropP.x - 
		offsetSign.x));

	p->SetPosition(ropP - p->GetBoxColliderOffset() 
		- offsetSign);

	previousR = ropP;


	return nullptr;
}

void SwingingState::OnExit()
{
}



void SwingingState::pSetRope(float2* _pRopePoints)
{
	ropePoint = _pRopePoints;
}
