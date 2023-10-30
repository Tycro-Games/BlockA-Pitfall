#include "precomp.h"
#include "ZipliningState.h"

void ZipliningState::OnEnter(Avatar& _p)
{
	cout << "zipline'\n";
	p = &_p;
	distance = 0;
	originalLeng = length(ziplineEnd - p->GetCollisionChecker()->GetBoxColliderPos());
	direction = normalize(ziplineEnd - ziplineStart);
	wholeLeng = length(ziplineEnd - ziplineStart);
	p->SetVelocityY(0);
	p->GetSubject()->Notify(0, ZOOM);
}

PlayerState* ZipliningState::Update(float deltaTime)
{
	const CollisionChecker* col = p->GetCollisionChecker();

	const Box* floorCollider = col->GetFloorCollider();
	const Box* boxCollider = col->GetBoxCollider();
	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!col->IsCollidingFloors(floorCollider) &&
			!col->IsCollidingFloors(boxCollider))
		{
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
		const float afterVelocity = invlerp(0, wholeLeng, distance * 2);
		clamp(afterVelocity, 0.0f, 1.0f);
		p->SetVelocityX(direction.x * afterVelocity * maxVelocity);
		p->ResetClimbTimer();
		return new FreemovingState();
	}
	return nullptr;
}

void ZipliningState::OnExit()
{
	p->GetSubject()->Notify(1, ZOOM);
}

void ZipliningState::SetZiplineEnd(float2 end)
{
	ziplineEnd = end;
}

void ZipliningState::SetZiplineStart(float2 start)
{
	ziplineStart = start;
}
