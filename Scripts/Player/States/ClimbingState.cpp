#include "precomp.h"
#include "ClimbingState.h"


void ClimbingState::OnEnter(Avatar& p)
{
	cout << "climbing state'\n";
	SetVariables(p);
	climbTimer = p.GetClimbTimer();
	velocity->y = 0;
}

State* ClimbingState::Update(Avatar& player, Input input, float deltaTime)
{
	if(input.jumping==true)
	{
		if (!floors->IsCollidingBox(*pos, *floorCollider) &&
			!floors->IsCollidingBox(*pos, *boxCollider)) {
			velocity->y = -CLIMBING_JUMP_FORCE;
			climbTimer->reset();
			return new FallingState();
		}
	}
	float2 newPos = {};

	
	
	const float newPosY = (velocity->y + static_cast<float>(input.arrowKeys.y)) * speed * deltaTime;


	newPos = *pos + float2{ 0, newPosY };
	if (ladders->IsCollidingBox(newPos, *boxCollider)) {
		if (Camera::OnScreen(newPos - cam->GetPosition(), *boxCollider))
		{
			*pos = newPos;
		}
	}
	else if (!floors->IsCollidingBox(newPos, *boxCollider)) {
		if (Camera::OnScreen(newPos - cam->GetPosition(), *boxCollider))
		{
			*pos = newPos;
		}
	}
	if(!ladders->IsCollidingBox(*pos, *boxCollider))
	{
		return new FallingState();
	}
	return nullptr;
}

void ClimbingState::OnExit()
{
}
