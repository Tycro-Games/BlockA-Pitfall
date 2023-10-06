#pragma once

class Monkey : public Enemy
{
public:
	void Render(Surface* screen) override;
	~Monkey() override;
	void Update(float deltaTime) override;
	float GetDistanceToPlayer() override;
	void Init(const float2& pos, Tilemap* floors, Tilemap* ladders, Avatar& p);
	static float GetValueFromMonkeyFunction(float t, bool positive);
	CollisionChecker* GetCollisionChecker() const;
private:
	MonkeyState* currentState = nullptr;

	const float DISTANCE_TO_PLAYER=15;
	const int DAMAGE=10;
	CollisionChecker* colCheck = nullptr;
	
};
