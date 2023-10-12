#pragma once

class SpawnRocks
{
public:
	//updates rocks
	SpawnRocks(CollisionChecker& _coll);
	~SpawnRocks();
	void Update(float deltaTime);
	 void Render(Surface* screen);
	void AddRockToActive(const float2& dir, const float2& pos);
	Array<Rock*>& GetActiveRocks();
private:
	Timer* timer = nullptr;
	const float FIRE_RATE = .1f;
	Array<Rock*> activeRocks;
	const uint8_t MAX_ROCK_NUMBER = 50;
	CollisionChecker* coll = nullptr;
};
