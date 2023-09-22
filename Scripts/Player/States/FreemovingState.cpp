#include "precomp.h"
#include "FreemovingState.h"
void FreemovingState::OnEnter()
{
}

void FreemovingState::Update(Avatar& p, Input input, float deltaTime)
{


	const float newPosX = (p.GetVelocity().x + static_cast<float>(input.arrowKeys.x)) * p.GetSpeed() * deltaTime;
	const float newPosY = p.GetVelocity().y * p.GetSpeed() * deltaTime;
	float2 pos = p.GetPos();
	float2 newPos = pos + float2{ newPosX, 0 };
	Tilemap* floors = p.GetFloors();
	Camera* cam = p.GetCamera();
	Box floorCollider = p.GetFloorCollider();
	Box boxCollider = p.GetBoxCollider();
	float2 velocity = p.GetVelocity();
	if (!floors->IsCollidingBox(newPos, floorCollider) && !floors->IsCollidingBox(newPos, boxCollider)) {
		if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;

		}
	}


	newPos = pos + float2{ 0, newPosY };

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
		return;
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

void FreemovingState::OnExit()
{

}
