#include "precomp.h"
#include "ClimbingState.h"


void ClimbingState::OnEnter(Avatar& _p)
{
	cout << "climbing'\n";
	p = &_p;
	p->SetVelocityY(0);
}

PlayerState* ClimbingState::Update(float deltaTime)
{

	if (floorPos.y < 0) {

		const Box floorCollider = p->GetFloorCollider();
		const Box boxCollider = p->GetBoxCollider();
		if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
		{
			if (!p->IsCollidingFloors(floorCollider) &&
				!p->IsCollidingFloors(boxCollider)) {
				p->SetVelocityY(-CLIMBING_JUMP_FORCE);
				p->ResetClimbTimer();
				p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x));
				return new FreemovingState();
			}
		}


		const float newPosY = (p->GetVelocity().y + static_cast<float>(p->GetInput().arrowKeys.y)) * p->GetSpeed() * deltaTime;


		float2 newPos = p->GetPos() + float2{ 0, newPosY };
		if (p->IsCollidingLadders(newPos, boxCollider)) {
			if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
			{
				p->SetPosition(newPos);
			}
		}
		else if (!p->IsCollidingFloors(newPos, boxCollider)) {
			if (Camera::SmallerThanScreenComplete(newPos, boxCollider))
			{
				p->SetPosition(newPos);
			}
		}
		if (!p->IsCollidingLadders(boxCollider))
		{
			//this is the end of a rope

			if (p->IsCollidingFloors(floorCollider, floorPos)) {
				floorPos.y = floorPos.y - floorCollider.max.y * 0.6f;
				originalPlayerPos = p->GetPos();
			}



		}
		return nullptr;

	}

	return ToTheEndOfTheLadder(deltaTime);



}

void ClimbingState::OnExit()
{
}

PlayerState* ClimbingState::ToTheEndOfTheLadder(float deltaTime)
{
	//lerp
	currentTime += deltaTime;
	if (currentTime < totalTimeToClimb) {
		//t is currentTime divided by total time inside  [0,1]
		const float t = currentTime / totalTimeToClimb;
		p->SetPositionY(lerp(originalPlayerPos.y, floorPos.y, t));
	}
	else {
		p->SetVelocityY(0);
		//return null
		return new FreemovingState();
	}
	return nullptr;
}
