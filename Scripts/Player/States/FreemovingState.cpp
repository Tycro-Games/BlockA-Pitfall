#include "precomp.h"
#include "FreemovingState.h"

void FreemovingState::OnEnter(Avatar& _p)
{
	cout << "Freemoving'\n";

	p = &_p;
}


void FreemovingState::AddJumpForce(const CollisionChecker* col, const Box* jumpCollider)
{
	if (p->GetInput().jumping == true)
	{
		if (col->IsCollidingFloors(p->GetPos(), jumpCollider))
		{
			p->SetVelocityY(-JUMP_FORCE);
			p->PlayJumpSound();
		}
	}
	else if (p->GetInput().smallJump == true)
	{
		if (col->IsCollidingFloors(p->GetPos(), jumpCollider))
		{
			p->SetVelocityY(-SMALL_JUMP_FORCE);
			p->PlayJumpSound();
		}
	}
}

void FreemovingState::ClampHorizontalMovement(const int signX) const
{
	const float direction = static_cast<float>(p->GetInput().arrowKeys.x) * modifierX;

	if (abs(p->GetVelocity().x) <= MAX_HORIZONTAL_INPUT_SPEED)
	{
		if (signX == 1)
		{
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
	p->SetVelocityX(clamp(p->GetVelocity().x, -MAX_HORIZONTAL_SPEED, MAX_HORIZONTAL_SPEED));
}


bool FreemovingState::CheckNonTiles(const CollisionChecker* col, const Box* floorCollider, const Box* boxCollider,
                                    PlayerState*& state)
{
	if (p->IsClimbTimerFinished(CLIMB_DELAY))
	{
		float2 normal = 0;
		float2 start = 0;
		float2 end = 0;

		if (col->IsCollidingZiplines(normal, start, end))
		{
			p->TranslatePosition(-normal); //snaps player to the zipline
			p->ResetClimbTimer();

			ZipliningState* zip = new ZipliningState();

			zip->SetZiplineEnd(end);
			zip->SetZiplineStart(start);
			state = zip;
			return true;
		}


		float2* movingPart = nullptr;
		if (col->IsCollidingRopes(movingPart))
		{
			p->ResetClimbTimer();
			p->SetVelocity(0);

			SwingingState* swing = new SwingingState();
			swing->pSetRope(movingPart);
			state = swing;
			return true;
		}
		ElasticPlant* pElastic = nullptr;
		if (col->IsCollidingElasticPlant(pElastic))
		{
			p->ResetClimbTimer();
			p->SetVelocity(0);

			ElasticPlantState* elasticState = new ElasticPlantState();
			elasticState->pSetPlant(pElastic);
			state = elasticState;
			return true;
		}
		float2 floorPos = 0;
		if (col->IsCollidingLadders(boxCollider, floorPos))
		{
			p->ResetClimbTimer();
			p->SetVelocity(0);
			originalPlayerPos = p->GetPos();
			ladderPositionX = floorPos.x + floorCollider->max.x + boxCollider->max.x / 2;
			//smooths to this out of the update method
		}
	}
	return false;
}

void FreemovingState::MoveOnFloor(float deltaTime, const CollisionChecker* col, const Box* floorCollider,
                                  const Box* boxCollider)
{
	const float newPosX = p->GetVelocity().x * p->GetSpeed() * deltaTime;
	float2 newPos = p->GetPos() + float2{newPosX, 0};

	if (!col->IsCollidingFloors(newPos, floorCollider))
	{
		//we are on the ground
		if (!col->IsCollidingFloors(newPos, boxCollider))
			if (Camera::SmallerThanScreenCompleteCollision(newPos, *boxCollider))
			{
				p->SetPosition(newPos);
			}
	}
	//on Y check
	const float newPosY = p->GetVelocity().y * p->GetSpeed() * deltaTime;
	newPos = p->GetPos() + float2{0, newPosY};

	if (!col->IsCollidingFloors(newPos, floorCollider))
	{
		if (Camera::SmallerThanScreenCompleteCollision(newPos, *boxCollider))
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
}

bool FreemovingState::UpdateVelocity(float deltaTime) const
{
	//wait for the peak of the jump
	if (p->GetVelocity().y < 0)
	{
		p->SetVelocityY(clamp(GRAVITY * deltaTime + p->GetVelocity().y,
		                      p->GetVelocity().y, GRAVITY));

		return true;
	}
	//momentum on horizontal
	if (abs(p->GetVelocity().x) > 0.2f)
	{
		p->SetVelocityX(p->GetVelocity().x - HORIZONTAL_GRAVITY
			* deltaTime * MathLibrary::Sign(p->GetVelocity().x));
	}
	else
	{
		p->SetVelocityX(0);
	}
	//fall
	p->SetVelocityY(clamp(GRAVITY * deltaTime + p->GetVelocity().y,
	                      p->GetVelocity().y, GRAVITY));
	return false;
}

PlayerState* FreemovingState::Update(float deltaTime)
{
	if (ladderPositionX < 0)
	{
		const CollisionChecker* col = p->GetCollisionChecker();
		const Box* floorCollider = col->GetFloorCollider();
		const Box* boxCollider = col->GetBoxCollider();
		const Box* jumpCollider = col->GetJumpCollider();
		//throw rock
		const Input input = p->GetInput();

		if (input.shooting)
		{
			const float2 dirToThrow = float2{static_cast<float>(-p->GetFlip()), input.arrowKeys.y < 0 ? -1.0f : 0.0f};
			p->ThrowRock(normalize(dirToThrow));
		}
		//only on floor
		AddJumpForce(col, jumpCollider);
		//add some horizontal velocity
		ClampHorizontalMovement(static_cast<int>(MathLibrary::Sign(p->GetVelocity().x)));

		//collision check
		MoveOnFloor(deltaTime, col, floorCollider, boxCollider);


		PlayerState* state = nullptr;

		if (UpdateVelocity(deltaTime))
			return state;

		if (CheckNonTiles(col, floorCollider, boxCollider, state))
			return state;


		return state;
	}
	//Smooth exit transition to the ladder

	return ToTheLadder(deltaTime);
}


void FreemovingState::OnExit()
{
}

PlayerState* FreemovingState::ToTheLadder(float deltaTime)
{
	//lerp
	currentTime += deltaTime;
	if (currentTime < totalTimeToLadder)
	{
		//t is currentTime divided by total time inside  [0,1]
		const float t = currentTime / totalTimeToLadder;
		p->SetPositionX(lerp(originalPlayerPos.x, ladderPositionX, t));
	}
	else
	{
		p->SetVelocityX(0);
		//return null
		return new ClimbingState();
	}
	return nullptr;
}
