#include "precomp.h"
#include "MovingOnGroundState.h"
void MovingOnGroundState::OnEnter(Avatar& p)
{
	SetVariables(p);

}



State* MovingOnGroundState::Update(Avatar& p, Input input, float deltaTime)
{
	float2 newPos = {};


	const float newPosY = velocity->y * speed * deltaTime;

	const float newPosX = (velocity->x + static_cast<float>(input.arrowKeys.x)) * speed * deltaTime;
	newPos = *pos + float2{ newPosX, 0 };

	if (!floors->IsCollidingBox(newPos, *floorCollider)) { //we are on the ground
		if (!floors->IsCollidingBox(newPos, *boxCollider))
			if (Camera::OnScreen(newPos - cam->GetPosition(), *boxCollider))
			{
				*pos = newPos;

			}
	}

	newPos = *pos + float2{ 0, newPosY };

	if (!floors->IsCollidingBox(newPos, *floorCollider)) //no floor
	{
		// go to the falling state
		cout << "To falling state\n";
		return new FallingState();

	}
	if (input.jumping == true && floors->IsCollidingBox(*pos + FLOOR_POS, *floorCollider))//on floor
	{
		//go to the jumping state
		cout << "To falling state jumping\n";
		p.SetVelocity(-JUMP_FORCE);
		return new FallingState();
	}


	return nullptr;


}

void MovingOnGroundState::OnExit()
{

}
