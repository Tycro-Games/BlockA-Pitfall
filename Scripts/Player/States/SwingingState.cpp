#include "precomp.h"
#include "SwingingState.h"

void SwingingState::OnEnter(Avatar& p)
{
	SetVariables(p);
	cout << "swinging'\n";

}

State* SwingingState::Update(float deltaTime)
{
	if (input->jumping == true)
	{
		if (!floors->IsCollidingBox(*pos, *floorCollider) &&
			!floors->IsCollidingBox(*pos, *boxCollider)) {
			velocity->x = static_cast<float>(input->arrowKeys.x) * SWINGING_JUMP_SPEED;
			velocity->y = -SWINGING_JUMP_SPEED;
			climbTimer->reset();

			return new FreemovingState();
		}
	}
	velocity->x = -(pos->x - ropePoint->x + BOX_OFFSET.x);
	*pos = *ropePoint - BOX_OFFSET;
	return nullptr;
}

void SwingingState::OnExit()
{
}

void SwingingState::SetVariables(Avatar& p)
{
	pos = p.pGetPos();
	velocity = p.pGetVelocity();
	BOX_OFFSET = p.GetBoxColliderOffset();
	floors = p.GetFloors();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	climbTimer = p.GetClimbTimer();
	floorPosCollider = p.getFloorPos();
}

void SwingingState::pSetRope(float2* p)
{
	ropePoint = p;
}
