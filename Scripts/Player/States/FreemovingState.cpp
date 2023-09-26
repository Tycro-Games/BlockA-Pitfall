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
	int signX = velocity->x > 0 ? 1 : -1;
	float direction = static_cast<float>(input->arrowKeys.x) * modifierX;
	if (signX == 1) {
		if (velocity->x + direction <= MAX_HORIZONTAL_SPEED)
		{
			velocity->x = velocity->x + direction;
		}
		else
		{
			velocity->x = MAX_HORIZONTAL_SPEED;
		}
	}
	else if (velocity->x + direction >= -MAX_HORIZONTAL_SPEED)
	{
		velocity->x = velocity->x + direction;

	}
	else
	{
		velocity->x = -MAX_HORIZONTAL_SPEED;
		
	}
	const float newPosX = velocity->x * speed * deltaTime;
	newPos = *pos + float2{ newPosX, 0 };

	if (!floors->IsCollidingBox(newPos, *floorCollider)) { //we are on the ground
		if (!floors->IsCollidingBox(newPos, *boxCollider))
			if (Camera::SmallerThanScreenComplete(newPos, *boxCollider))
			{
				*pos = newPos;

			}
	}
	//floor check

	newPos = *pos + float2{ 0, newPosY };

	if (!floors->IsCollidingBox(newPos, *floorCollider))
	{
		if (Camera::SmallerThanScreenComplete(newPos, *boxCollider))
		{
			*pos = newPos;
			modifierX = IN_AIR_MODIFIED_X;

		}

	}
	else
	{
		modifierX = ON_GROUND_MODIFIED_X;
		velocity->y = 0;//hit something up so stop velocity 
		climbTimer->reset();
	}

	//checks for floor snapping
	float2 floorPos = { 0 };

	if (velocity->y < 0) {//wait for the peak of the jump
		velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);
		return nullptr;
	}
	if (abs(velocity->x) > 0.1f) {
		if (input->arrowKeys.x == 0)
			velocity->x -= HORIZONTAL_GRAVITY * deltaTime * signX;
	}
	else
	{
		velocity->x = 0;
	}
	velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);



	//check for ladders
	if (climbTimer->elapsed() >= CLIMB_DELAY &&
		ladders->IsCollidingBox(*pos, *boxCollider, floorPos)) {
		climbTimer->reset();
		*pos = floorPos + floorCollider->max.x + boxCollider->max.x / 2;
		velocity->y = 0;
		velocity->x = 0;
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
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	climbTimer = p.GetClimbTimer();
	ladders = p.GetLadders();
	floorPosCollider = p.getFloorPos();
}

