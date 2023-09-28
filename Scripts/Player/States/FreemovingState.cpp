#include "precomp.h"
#include "FreemovingState.h"

void FreemovingState::OnEnter(Avatar& _p)
{
	cout << "Freemoving'\n";

	SetVariables(_p);
	p = &_p;
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
	if (input->smallJump == true)
	{

		if (floors->IsCollidingBox(*pos + floorPosCollider, *floorCollider))
		{
			velocity->y = -SMALL_JUMP_FORCE;
		}

	}
	float2 newPos = {};


#pragma region
	int signX = velocity->x > 0 ? 1 : -1;
	float direction = static_cast<float>(input->arrowKeys.x) * modifierX;

	if (abs(velocity->x) <= MAX_HORIZONTAL_INPUT_SPEED) {
		if (signX == 1) {
			if (velocity->x + direction <= MAX_HORIZONTAL_INPUT_SPEED)
			{
				velocity->x = velocity->x + direction;
			}
			else
			{
				velocity->x = MAX_HORIZONTAL_INPUT_SPEED;
			}

		}
		else if (velocity->x + direction >= -MAX_HORIZONTAL_INPUT_SPEED)
		{

			velocity->x = velocity->x + direction;

		}
		else
		{
			velocity->x = -MAX_HORIZONTAL_INPUT_SPEED;

		}
	}
	velocity->x = clamp(velocity->x, -MAX_HORIZONTAL_SPEED, MAX_HORIZONTAL_SPEED);
#pragma endregion Horizontal

	const float newPosX = velocity->x * speed * deltaTime;
	newPos = p->GetPos() + float2{ newPosX, 0 };

	if (!floors->IsCollidingBox(newPos, *floorCollider)) { //we are on the ground
		if (!floors->IsCollidingBox(newPos, *boxCollider))
			if (Camera::SmallerThanScreenComplete(newPos, *boxCollider))
			{
				*pos = newPos;

			}
	}
	//on Y check
	const float newPosY = p->GetVelocity().y * speed * deltaTime;
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
	if (abs(velocity->x) > 0.2f) {

		velocity->x -= HORIZONTAL_GRAVITY * deltaTime * signX;
	}
	else
	{
		velocity->x = 0;
	}



	velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);

	//check for zipline
	if (p->IsClimbTimerFinished(CLIMB_DELAY))
	{
		float2 normal = 0;
		float2 start = 0;
		float2 end = 0;

		if (p->IsCollidingZiplines(normal, start, end)) {
			p->TransaltePosition(-normal);//snaps player to the zipline
			p->ResetClimbTimer();

			ZipliningState* zip = new ZipliningState();

			zip->SetZiplineEnd(end);
			zip->SetZiplineStart(start);
			return zip;

		}


		float2* movingPart = nullptr;
		if (p->IsCollidingRopes(movingPart))
		{
			velocity->x = 0;
			velocity->y = 0;
			p->ResetClimbTimer();
			p->SetVelocity(0);

			SwingingState* swing = new SwingingState();
			swing->pSetRope(movingPart);
			return swing;
		}
		if (p->IsCollidingLadders(floorPos)) {
			p->ResetClimbTimer();
			p->SetVelocity(0);

			p->SetPostion(floorPos + floorCollider->max.x + boxCollider->max.x / 2);
			return new ClimbingState();
		}
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
	floorPosCollider = p.getFloorPos();
	ropes = p.GetRopes();
	ropeCount = p.GetRopeCount();
	ziplineCount = p.GetZiplinesCount();
	ziplines = p.GetZiplines();
}

