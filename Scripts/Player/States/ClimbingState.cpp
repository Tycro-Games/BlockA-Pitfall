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
		const CollisionChecker* col = p->GetCollisionChecker();

		const Box* floorCollider = col->GetFloorCollider();
		const Box* boxCollider = col->GetBoxCollider();
		if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
		{
			if (!col->IsCollidingFloors(floorCollider) &&
				!col->IsCollidingFloors(boxCollider)) {
				p->SetVelocityY(-CLIMBING_JUMP_FORCE);
				p->ResetClimbTimer();
				p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x));
				return new FreemovingState();
			}
		}
		const Input input = p->GetInput();

		if (input.shooting)
		{

			const float2 dirToThrow = float2{ static_cast<float>(-p->GetFlip()), input.arrowKeys.x != 0 ? 0.0f: 1.0f };
			p->ThrowRock(normalize(dirToThrow));
		}
		p->SetVelocityX(static_cast<float>(p->GetInput().arrowKeys.x));
		const float newPosY = (p->GetVelocity().y + static_cast<float>(p->GetInput().arrowKeys.y)) * p->GetSpeed() * deltaTime;


		const float2 newPos = p->GetPos() + float2{ 0, newPosY };
		if (col->IsCollidingLadders(newPos, boxCollider)) {
			if (Camera::SmallerThanScreenCompleteCollision(newPos, *boxCollider))
			{
				p->SetPosition(newPos);
			}
		}
		else if (!col->IsCollidingFloors(newPos, boxCollider)) {
			if (Camera::SmallerThanScreenCompleteCollision(newPos, *boxCollider))
			{
				p->SetPosition(newPos);
			}
		}
		if (!col->IsCollidingLadders(boxCollider))
		{
			//this is the end of a rope

			if (col->IsCollidingFloors(floorCollider, floorPos)) {
				floorPos.y = floorPos.y - floorCollider->max.y * 0.6f;
				originalPlayerPos = p->GetPos();
			}
			else
			{
				return new FreemovingState();
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
