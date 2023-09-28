#include "precomp.h"
#include "ZipliningState.h"

void ZipliningState::OnEnter(Avatar& p)
{
	SetVariables(p);
	cout << "zipline'\n";

	distance = 0;
	originalPos = *pos;
	originalLeng = length(ziplineEnd - originalPos + BOX_OFFSET);
	direction = normalize(ziplineEnd - ziplineStart);
	wholeLeng = length(ziplineEnd - ziplineStart);
}

State* ZipliningState::Update(float deltaTime)
{
	if (input->jumping == true || input->smallJump == true)
	{
		if (!floors->IsCollidingBox(*pos, *floorCollider) &&
			!floors->IsCollidingBox(*pos, *boxCollider)) {
			velocity->x = 0;
			climbTimer->reset();

			velocity->y = -ZIPLINE_JUMP_SPEED;
			return new FreemovingState();
		}

	}

	distance += deltaTime * MAX_SPEED;
	*pos += direction * deltaTime * MAX_SPEED;
	//keeps player facing the right way
	velocity->x = direction.x;

	if (originalLeng <= distance)
	{
		float afterVelocity =  invlerp(0, wholeLeng, distance*2);
		clamp(afterVelocity, 0.0f, 1.0f);
		velocity->x = direction.x * afterVelocity*maxVelocity;
		climbTimer->reset();
		return new FreemovingState();
	}
	return nullptr;
}

void ZipliningState::OnExit()
{
}

void ZipliningState::SetZiplineEnd(float2 end)
{
	ziplineEnd = end;
}void ZipliningState::SetZiplineStart(float2 start)
{
	ziplineStart = start;
}

void ZipliningState::SetVariables(Avatar& p)
{
	pos = p.pGetPos();
	velocity = p.pGetVelocity();
	BOX_OFFSET = p.GetBoxColliderOffset();
	floors = p.GetFloors();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
	input = p.pGetInput();
	climbTimer = p.GetClimbTimer();
	ladders = p.GetLadders();
	floorPosCollider = p.getFloorPos();
}
