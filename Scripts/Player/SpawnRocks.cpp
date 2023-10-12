#include "precomp.h"
#include "SpawnRocks.h"


SpawnRocks::SpawnRocks(CollisionChecker& _coll)
{
	activeRocks.Init(MAX_ROCK_NUMBER);

	timer = new Timer();
	for (uint i = 0; i < activeRocks.GetCount(); i++)
	{

		activeRocks[i] = new Rock();
	}

	coll = &_coll;
}

SpawnRocks::~SpawnRocks()
{
	delete timer;
}

void SpawnRocks::Update(float deltaTime)
{

	for (uint i = 0; i < activeRocks.GetCount(); i++)
	{
		if (activeRocks[i]->GetActive()) {

			activeRocks[i]->Update(deltaTime);
			float2 rockPos = activeRocks[i]->GetPosition();
			Box rockCollider = activeRocks[i]->GetBoxCollider();
			if (coll->IsInGameBounds(rockPos, &rockCollider)) {
				if (coll->IsCollidingFloors(rockPos, &rockCollider))
				{
					activeRocks[i]->SetActive(false);

				}
			}
			else
			{
				activeRocks[i]->SetActive(false);
			}
		}
	}
}

void SpawnRocks::Render(Surface* screen)
{
	for (uint i = 0; i < MAX_ROCK_NUMBER; i++) {
		if (activeRocks[i]->GetActive()) {
			const float2 rockPos = activeRocks[i]->GetPosition();

			const Box box = activeRocks[i]->GetBoxCollider();
			const float2 camPos = Camera::GetPosition();

			const int x1 = static_cast<int>(rockPos.x + box.min.x - camPos.x);
			const int y1 = static_cast<int>(rockPos.y + box.min.y - camPos.y);

			const int x2 = static_cast<int>(rockPos.x + box.max.x - camPos.x);
			const int y2 = static_cast<int>(rockPos.y + box.max.y - camPos.y);
			screen->Box(x1, y1, x2, y2, PINK);
		}

	}
}

void SpawnRocks::AddRockToActive(const float2& dir, const float2& pos)
{
	if(timer->elapsedF()>FIRE_RATE)
	for (uint i = 0; i < MAX_ROCK_NUMBER; i++)
	{
		if (!activeRocks[i]->GetActive()) {
			timer->reset();
			activeRocks[i]->Init(pos, dir);
			activeRocks[i]->SetActive(true);
			break;
		}


	}

}

Array<Rock*>& SpawnRocks::GetActiveRocks()
{
	return activeRocks;
}
