﻿#include "precomp.h"
#include "SpawnRocks.h"


SpawnRocks::SpawnRocks(CollisionChecker& _coll)
{
	activeRocks.Init(MAX_ROCK_NUMBER);

	timer = new Timer();

	rockSprite = new Sprite(new Surface("assets/rock_16x16.png"), 1);
	Surface* surf = new Surface(RESIZE, RESIZE);
	surf->Clear(0xf00);
	preRenderSprite = new Sprite(surf, 1);
	surf->Clear(0);

	rockSprite->DrawScaled(0, 0, RESIZE, RESIZE, preRenderSprite->GetSurface());

	coll = &_coll;
}

SpawnRocks::~SpawnRocks()
{
	delete timer;
	delete preRenderSprite;
	delete rockSprite;
}


void SpawnRocks::Update(float deltaTime)
{
	for (uint i = 0; i < activeRocks.Size(); i++)
	{
		if (activeRocks[i].GetActive())
		{
			activeRocks[i].Update(deltaTime);
			float2 rockPos = activeRocks[i].GetPosition();
			Box rockCollider = activeRocks[i].GetBoxCollider();
			if (coll->IsInGameBounds(rockPos, &rockCollider))
			{
				if (coll->IsCollidingFloors(rockPos, &rockCollider))
				{
					activeRocks[i].SetActive(false);
				}
			}
			else
			{
				activeRocks[i].SetActive(false);
			}
		}
	}
}

void SpawnRocks::Render(Surface* screen)
{
	for (uint i = 0; i < MAX_ROCK_NUMBER; i++)
	{
		if (activeRocks[i].GetActive())
		{
			const float2 rockPos = activeRocks[i].GetPosition();

			const Box box = activeRocks[i].GetBoxCollider();
			const float2 camPos = Camera::GetPosition();

			const int x1 = static_cast<int>(rockPos.x + box.min.x - camPos.x);
			const int y1 = static_cast<int>(rockPos.y + box.min.y - camPos.y);
#ifdef _DEBUG
			const int x2 = static_cast<int>(rockPos.x + box.max.x - camPos.x);
			const int y2 = static_cast<int>(rockPos.y + box.max.y - camPos.y);
			screen->Box(x1, y1, x2, y2, PINK);
#endif
			//rockSprite->Draw(screen, x1, y1);
			preRenderSprite->DrawScaled(x1, y1, RESIZE, RESIZE, screen);
		}
	}
}

void SpawnRocks::AddRockToActive(const float2& dir, const float2& pos)
{
	if (timer->elapsedF() > FIRE_RATE)
		for (uint i = 0; i < MAX_ROCK_NUMBER; i++)
		{
			if (!activeRocks[i].GetActive())
			{
				timer->reset();
				activeRocks[i].Init(pos, dir);
				activeRocks[i].SetActive(true);
				break;
			}
		}
}

StaticArray<Rock>& SpawnRocks::GetActiveRocks()
{
	return activeRocks;
}

Surface* SpawnRocks::GetRockSprite() const
{
	return preRenderSprite->GetSurface();
}
