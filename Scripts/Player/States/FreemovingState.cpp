#include "precomp.h"
#include "FreemovingState.h"

void FreemovingState::OnEnter(Avatar& p)
{
	SetVariables(p);
	cout << "FReemoving'\n";

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
		if (abs(velocity->x) > 0.2f) {

			velocity->x -= HORIZONTAL_GRAVITY * deltaTime * signX;
		}
		else
		{
			velocity->x = 0;
		}
	
	
	
	velocity->y = clamp(GRAVITY * deltaTime + velocity->y, velocity->y, GRAVITY);

	//check for zipline
	if (climbTimer->elapsed() >= CLIMB_DELAY)
	{
		for (uint i = 0; i < ziplineCount; i++)
			if (ziplines[i].GetOnScreen()) {
				float2 start = 0;
				float2 end = 0;
				ziplines[i].GetStartEnd(start, end);

				float2 a = end - start;
				float2 toPlayer = -(start - (*pos + BOX_POS));
				float2 toPlayerP = normalize(a) * clamp(length(toPlayer), 0.0f, length(a)-ZIPLINE_OFFSET_END);//not after the end
				float2 normal = toPlayer - toPlayerP;
				if (length(normal) <= RADIUS_TO_ZIPLINE) {
					*pos -= normal;//snaps player to the zipline
					velocity->x = 0;
					velocity->y = 0;
					ZipliningState* zip = new ZipliningState();
					climbTimer->reset();
					zip->SetZiplineEnd(end);
					zip->SetZiplineStart(start);
					return zip;

				}
			}
		for (uint i = 0; i < ropeCount; i++) {
			if (ropes[i].GetOnScreen()) {


				float2 toPlayer = (*pos + BOX_POS) - ropes[i].GetMovingPart();
				if (length(toPlayer) <= RADIUS_TO_ROPE) {
					velocity->x = 0;
					velocity->y = 0;
					climbTimer->reset();

					SwingingState* swing = new SwingingState();
					swing->pSetRope(ropes[i].pGetMovingPart());
					return swing;
				}
			}
		}
		if (ladders->IsCollidingBox(*pos, *boxCollider, floorPos)) {
			climbTimer->reset();
			*pos = floorPos + floorCollider->max.x + boxCollider->max.x / 2;
			velocity->y = 0;
			velocity->x = 0;
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
	BOX_POS = p.GetBoxColliderOffset();
	floors = p.GetFloors();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	climbTimer = p.GetClimbTimer();
	ladders = p.GetLadders();
	floorPosCollider = p.getFloorPos();
	ropes = p.GetRopes();
	ropeCount = p.GetRopeCount();
	ziplineCount = p.GetZiplinesCount();
	ziplines = p.GetZiplines();
}

