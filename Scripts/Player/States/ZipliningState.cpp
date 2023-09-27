#include "precomp.h"
#include "ZipliningState.h"

void ZipliningState::OnEnter(Avatar& p)
{
	SetVariables(p);

	originalPos = *pos;
	originalLeng = length(ziplineEnd - originalPos + BOX_OFFSET);
	direction = normalize(ziplineEnd - ziplineStart);
}

State* ZipliningState::Update(float deltaTime)
{
	if (input->jumping == true)
	{
		*velocity = direction * 2.25f;
		climbTimer->reset();

		velocity->y = -ZIPLINE_JUMP_SPEED;
		return new FreemovingState();

	}
	float dist = length(ziplineEnd - *pos);
	t = invlerp(originalLeng, 50.0f, dist);
	bool finished = false;
	if (t > 1) {
		t = 1;
		finished = true;
	}
	*pos += direction * deltaTime * MAX_SPEED;
	velocity->x = direction.x ;

	if (finished)
	{
		*velocity = direction * 2.5f;
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
