#include "precomp.h"
#include "SwingingState.h"

void SwingingState::OnEnter(Avatar& _p)
{
	cout << "swinging'\n";
	p = &_p;
	p->SetVelocityX(-(p->GetPos().x + p->GetCollisionChecker()->GetBoxColliderOffset().x - ropePoint->x + OFFSET_ROPE.x));
	previousR = *ropePoint;

	p->GetSubject()->Notify(0, ZOOM);
}

PlayerState* SwingingState::Update(float deltaTime)
{
	const CollisionChecker* col = p->GetCollisionChecker();

	const Box* floorCollider = col->GetFloorCollider();
	const Box* boxCollider = col->GetBoxCollider();
	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!col->IsCollidingFloors(floorCollider) &&
			!col->IsCollidingFloors(boxCollider)) {
			p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x) * SWINGING_JUMP_SPEED);
			if (p->GetInput().arrowKeys.x)
				p->SetVelocityY(-SWINGING_JUMP_SPEED);
			p->ResetClimbTimer();

			return new FreemovingState();
		}
	}
	float2 offsetSign = OFFSET_ROPE;
	const float2 ropP = *ropePoint;
	//left or right
	const float heading = previousR.x - ropP.x;
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
		col->GetBoxColliderOffset().x - ropP.x -
		offsetSign.x));

	p->SetPosition(ropP - col->GetBoxColliderOffset()
		- offsetSign);

	previousR = ropP;


	return nullptr;
}

void SwingingState::OnExit()
{
	p->GetSubject()->Notify(1, ZOOM);

}



void SwingingState::pSetRope(float2* _pRopePoints)
{
	ropePoint = _pRopePoints;
}
