#include "precomp.h"
#include "ClimbingState.h"


void ClimbingState::OnEnter(Avatar& p)
{
	SetVariables(p);

	velocity->y = 0;
}

State* ClimbingState::Update(float deltaTime)
{
	if (input->jumping == true)
	{
		if (!floors->IsCollidingBox(*pos, *floorCollider) &&
			!floors->IsCollidingBox(*pos, *boxCollider)) {
			velocity->y = -CLIMBING_JUMP_FORCE;
			climbTimer->reset();
			input->jumping = false;
			velocity->x = static_cast<float>(input->arrowKeys.x);
			return new FreemovingState();
		}
	}
	float2 newPos = 0;



	const float newPosY = (velocity->y + static_cast<float>(input->arrowKeys.y)) * speed * deltaTime;


	newPos = *pos + float2{ 0, newPosY };
	if (ladders->IsCollidingBox(newPos, *boxCollider)) {
		if (Camera::SmallerThanScreenComplete(newPos, *boxCollider))
		{
			*pos = newPos;
		}
	}
	else if (!floors->IsCollidingBox(newPos, *boxCollider)) {
		if (Camera::SmallerThanScreenComplete(newPos, *boxCollider))
		{
			*pos = newPos;
		}
	}
	if (!ladders->IsCollidingBox(*pos, *boxCollider))
	{
		//this is the end of a rope
		float2 floorPos = { 0 };

		if (floors->IsCollidingBox(*pos, *floorCollider, floorPos)) {
			floorPos.y = floorPos.y - boxCollider->max.y / 2 - floorCollider->max.y / 2;
			pos->y = floorPos.y;
			velocity->y = 0;
		}
		return new FreemovingState();
	}
	return nullptr;
}

void ClimbingState::OnExit()
{
}

void ClimbingState::SetVariables(Avatar& p)
{
	pos = p.pGetPos();
	velocity = p.pGetVelocity();

	floors = p.GetFloors();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	ladders = p.GetLadders();
	climbTimer = p.GetClimbTimer();
}
