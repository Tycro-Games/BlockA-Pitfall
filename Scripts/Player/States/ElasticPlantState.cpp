#include "precomp.h"
#include "ElasticPlantState.h"

void ElasticPlantState::OnEnter(Avatar& _p)
{
	p = &_p;
}

PlayerState* ElasticPlantState::Update(float deltaTime)
{
	deltaTime;//fixes warning C4100
	const CollisionChecker* col = p->GetCollisionChecker();

	const Box* floorCollider = col->GetFloorCollider();
	const Box* boxCollider = col->GetBoxCollider();
	const float2 elasticP = *elasticPoint;

	if (p->GetInput().jumping == true || p->GetInput().smallJump == true)
	{
		if (!col->IsCollidingFloors(floorCollider) &&
			!col->IsCollidingFloors(boxCollider)) {
			//modify for elastic
			const float2 lastY = normalize(elasticP - previousP);
			if (lastY.y < 0) {//going up
				cout << plant->GetPercentOfSpeed() << "\n";
				//this gives a value between 0 and 1
				float multiplier = plant->GetPercentOfSpeed();
				if (multiplier > MAX_THRESHOLD)
					multiplier = 1.0f;
				p->SetVelocityY(lastY.y * MAX_JUMP*multiplier);
			}
			else
			{
				p->SetVelocityY(0);

			}
			p->ResetClimbTimer();
			plant->SetActivation(false);

			return new FreemovingState();
		}
	}

	p->SetPosition(elasticP - col->GetBoxColliderOffset());

	previousP = elasticP;
	return nullptr;
}

void ElasticPlantState::OnExit()
{
}

void ElasticPlantState::pSetPlant(ElasticPlant* _plant)
{
	plant = _plant;
	plant->SetActivation(true);
	elasticPoint = plant->pGetPosition();
}

