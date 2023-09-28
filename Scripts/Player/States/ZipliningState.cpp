#include "precomp.h"
#include "ZipliningState.h"

void ZipliningState::OnEnter(Avatar& _p)
{
	cout << "zipline'\n";
	p = &_p;
	distance = 0;
	originalLeng = length(ziplineEnd - p->GetPos() + p->GetBoxColliderOffset());
	direction = normalize(ziplineEnd - ziplineStart);
	wholeLeng = length(ziplineEnd - ziplineStart);
}

PlayerState* ZipliningState::Update(float deltaTime)
{
	const Box floorCollider = p->GetFloorCollider();
	const Box boxCollider = p->GetBoxCollider();
	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!p->IsCollidingFloors(floorCollider) &&
			!p->IsCollidingFloors(boxCollider)) {
			p->SetVelocityX(0);
			p->SetVelocityY(-ZIPLINE_JUMP_SPEED);

			p->ResetClimbTimer();

			return new FreemovingState();
		}

	}

	distance += deltaTime * MAX_SPEED;
	p->TranslatePosition(direction * deltaTime * MAX_SPEED);
	//keeps player facing the right way
	p->SetVelocityX(direction.x);

	if (originalLeng <= distance)
	{
		float afterVelocity = invlerp(0, wholeLeng, distance * 2);
		clamp(afterVelocity, 0.0f, 1.0f);
		p->SetVelocityX(direction.x * afterVelocity * maxVelocity);
		p->ResetClimbTimer();
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


