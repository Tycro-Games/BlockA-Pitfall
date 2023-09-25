#include "precomp.h"
#include "FallingState.h"

void FallingState::OnEnter(Avatar& p)
{
	SetVariables(p);

}

State* FallingState::Update(Avatar& p, float deltaTime)
{
	if (input->jumping == true)
	{
		if (floors->IsCollidingBox(*pos + FLOOR_POS, *floorCollider))
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

	if (velocity->y < 0) {
		velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);
		return nullptr;
	}


	velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);



	//check for ladders
	if (climbTimer->elapsed() >= CLIMB_DELAY &&
		ladders->IsCollidingBox(*pos, *boxCollider, floorPos)) {
		climbTimer->reset();
		*pos = floorPos + floorCollider->max.x  + boxCollider->max.x / 2;
		velocity->y = 0;
		return new ClimbingState();
	}
	return nullptr;

}

void FallingState::OnExit()
{
}

void FallingState::SetVariables(Avatar& p)
{
	State::SetVariables(p);
	climbTimer = p.GetClimbTimer();
	ladders = p.GetLadders();

}

