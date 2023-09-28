#include "precomp.h"
#include "FreemovingState.h"

void FreemovingState::OnEnter(Avatar& _p)
{
	cout << "Freemoving'\n";

	p = &_p;
}



PlayerState* FreemovingState::Update(float deltaTime)
{
	const Box floorCollider = p->GetFloorCollider();
	const Box boxCollider = p->GetBoxCollider();
	if (p->GetInput().jumping == true)
	{

		if (p->IsCollidingFloors(p->GetPos() + p->getFloorPos(), floorCollider))
		{
			p->SetVelocityY(-JUMP_FORCE);

		}

	}
	if (p->GetInput().smallJump == true)
	{

		if (p->IsCollidingFloors(p->GetPos() + p->getFloorPos(), floorCollider))
		{
			p->SetVelocityY(-SMALL_JUMP_FORCE);

		}

	}
	float2 newPos = {};


#pragma region
	int signX = p->GetVelocity().x > 0 ? 1 : -1;
	float direction = static_cast<float>(p->GetInput().arrowKeys.x) * modifierX;

	if (abs(p->GetVelocity().x) <= MAX_HORIZONTAL_INPUT_SPEED) {
		if (signX == 1) {
			if (p->GetVelocity().x + direction <= MAX_HORIZONTAL_INPUT_SPEED)
			{
				p->SetVelocityX(p->GetVelocity().x + direction);
			}
			else
			{
				p->SetVelocityX(MAX_HORIZONTAL_INPUT_SPEED);
			}

		}
		else if (p->GetVelocity().x + direction >= -MAX_HORIZONTAL_INPUT_SPEED)
		{

			p->SetVelocityX(p->GetVelocity().x + direction);


		}
		else
		{
			p->SetVelocityX(-MAX_HORIZONTAL_INPUT_SPEED);
		}
	}
	p->SetVelocityX( clamp(p->GetVelocity().x, -MAX_HORIZONTAL_SPEED, MAX_HORIZONTAL_SPEED));
#pragma endregion Horizontal

	const float newPosX = p->GetVelocity().x * p->GetSpeed() * deltaTime;
	newPos = p->GetPos() + float2{ newPosX, 0 };

	if (!p->IsCollidingFloors(newPos, p->GetFloorCollider())) { //we are on the ground
		if (!p->IsCollidingFloors(newPos, p->GetBoxCollider()))
			if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
			{
				p->SetPosition(newPos);
			}
	}
	//on Y check
	const float newPosY = p->GetVelocity().y * p->GetSpeed() * deltaTime;
	newPos = p->GetPos() + float2{ 0, newPosY };

	if (!p->IsCollidingFloors(newPos, p->GetFloorCollider()))
	{
		if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
		{
			p->SetPosition(newPos);
			modifierX = IN_AIR_MODIFIED_X;

		}

	}
	else
	{
		modifierX = ON_GROUND_MODIFIED_X;
		p->SetVelocityY(0);
		p->ResetClimbTimer();
	}

	//checks for floor snapping
	float2 floorPos = { 0 };

	if (p->GetVelocity().y < 0) {//wait for the peak of the jump
		p->SetVelocityY(clamp(GRAVITY * deltaTime + p->GetVelocity().y, p->GetVelocity().y, GRAVITY));
		return nullptr;
	}
	if (abs(p->GetVelocity().x) > 0.2f) {

		p->SetVelocityX(p->GetVelocity().x - HORIZONTAL_GRAVITY * deltaTime * signX);

	}
	else
	{
		p->SetVelocityX(0);
	}

	p->SetVelocityY(clamp(GRAVITY * deltaTime + p->GetVelocity().y, p->GetVelocity().y, GRAVITY));


	//check for zipline
	if (p->IsClimbTimerFinished(CLIMB_DELAY))
	{
		float2 normal = 0;
		float2 start = 0;
		float2 end = 0;

		if (p->IsCollidingZiplines(normal, start, end)) {
			p->TranslatePosition(-normal);//snaps player to the zipline
			p->ResetClimbTimer();

			ZipliningState* zip = new ZipliningState();

			zip->SetZiplineEnd(end);
			zip->SetZiplineStart(start);
			return zip;

		}


		float2* movingPart = nullptr;
		if (p->IsCollidingRopes(movingPart))
		{
			p->ResetClimbTimer();
			p->SetVelocity(0);

			SwingingState* swing = new SwingingState();
			swing->pSetRope(movingPart);
			return swing;
		}
		if (p->IsCollidingLadders(boxCollider, floorPos)) {
			p->ResetClimbTimer();
			p->SetVelocity(0);

			p->SetPosition(floorPos + floorCollider.max.x + boxCollider.max.x / 2);
			return new ClimbingState();
		}
	}



	return nullptr;

}


void FreemovingState::OnExit()
{
}


