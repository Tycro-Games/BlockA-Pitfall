#include "precomp.h"
#include "FreemovingState.h"

void FreemovingState::OnEnter(Avatar& p)
{
	SetVariables(p);

	
}

State* FreemovingState::Update(float deltaTime)
{
	if (input->jumping == true)
	{
		if (floors->IsCollidingBox(*pos + floorPosCollider, *floorCollider))
		{
			velocity->y = -JUMP_FORCE;
		}

	}



	float2 newPos = {};


	const float newPosY = velocity->y * speed * deltaTime;

	const float newPosX = (velocity->x + static_cast<float>(input->arrowKeys.x)) * speed * deltaTime;
	newPos = *pos + float2{ newPosX, 0 };

	if (!floors->IsCollidingBox(newPos, *floorCollider)) { //we are on the ground
		if (!floors->IsCollidingBox(newPos, *boxCollider))
			if (Camera::OnScreen(newPos - cam->GetPosition(), *boxCollider))
			{
				*pos = newPos;

			}
	}
	//floor check

	newPos = *pos + float2{ 0, newPosY };

	if (!floors->IsCollidingBox(newPos, *floorCollider))
	{
		if (Camera::OnScreen(newPos - cam->GetPosition(), *boxCollider))
		{
			*pos = newPos;

		}

	}
	else
	{
		velocity->y = 0;//hit something up so stop velocity
	}

	//checks for floor snapping
	float2 floorPos = { 0 };

	if (velocity->y < 0) {//wait for the peak of the jump
		velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);
		return nullptr;
	}
	
	velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);



	//check for ladders
	if (climbTimer->elapsed() >= climbDelay &&
		ladders->IsCollidingBox(*pos, *boxCollider, floorPos)) {
		climbTimer->reset();
		*pos = floorPos + floorCollider->max.x + boxCollider->max.x / 2;
		velocity->y = 0;
		return new ClimbingState();
	}
	return nullptr;

}

void FreemovingState::OnExit()
{
}

void FreemovingState::SetVariables(Avatar& p)
{
	pos = p.pGetPos();
	velocity = p.pGetVelocity();

	floors = p.GetFloors();
	cam = p.GetCamera();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	climbTimer = p.GetClimbTimer();
	ladders = p.GetLadders();
	floorPosCollider = p.getFloorPos();
}

