#include "precomp.h"
#include "MovingOnGroundState.h"
void MovingOnGroundState::OnEnter()
{
}



State* MovingOnGroundState::Update(Avatar& p, Input _input, float deltaTime)
{
	float2 pos;
	float2 newPos;
	Tilemap* floors;
	Camera* cam;
	Box floorCollider;
	Box boxCollider;
	float2 velocity;
	SetVariables(p, deltaTime, pos, newPos, floors, cam, floorCollider, boxCollider, velocity);

	const float newPosY = p.GetVelocity().y * p.GetSpeed() * deltaTime;
	const float newPosX = (p.GetVelocity().x + static_cast<float>(input.arrowKeys.x)) * p.GetSpeed() * deltaTime;
	newPos = pos + float2{ newPosX, 0 };

	if (!floors->IsCollidingBox(newPos, floorCollider)) { //we are on the ground
		if (!floors->IsCollidingBox(newPos, boxCollider))
			if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
			{
				pos = newPos;

			}
	}

	newPos = pos + float2{ 0, newPosY };

	if (!floors->IsCollidingBox(newPos, floorCollider)) //no floor
	{
		// go to the falling state
		cout << "To falling state\n";
		return new FallingState();

	}
	if (input.jumping == true)//on floor
	{
		//go to the jumping state
		cout << "To jumping state\n";
		return new JumpingState();
	}


	return nullptr;
	if (!floors->IsCollidingBox(newPos, floorCollider))
	{
		if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;

		}

	}
	else
	{
		//hit something up so stop velocity
		p.SetVelocity(float2{ velocity.x, 0 });
	}
	//all in jump
	//early jump do not snap
	if (velocity.y < 0) {

		//velocity.y = clamp(GRAVITY * deltaTime + velocity.y, -JUMP_FORCE, GRAVITY);
	}
	//snap is on floor
	float2 floorPos;
	if (floors->IsCollidingBox(pos, floorCollider, floorPos)) {
		floorPos.y = floorPos.y - boxCollider.max.y / 2 - floorCollider.max.y / 2;
		pos.y = floorPos.y;
		velocity.y = 0;

	}
	//continue falling
	else
	{

		//velocity.y = clamp(GRAVITY * deltaTime + velocity.y, -JUMP_FORCE, GRAVITY);
	}

}

void MovingOnGroundState::OnExit()
{

}
