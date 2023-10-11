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
	Array<Rock*> activeRocks;
	Array<Rock*> inactiveRocks;
	const uint8_t MAX_ROCK_NUMBER = 10;
	CollisionChecker* coll = nullptr;
};
