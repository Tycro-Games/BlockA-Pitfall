#pragma once

class Monkey : public Enemy
{
public:
	void Render(Surface* screen) override;
	Box GetThrowCollider() const;
	bool SeesPlayer() const;
	~Monkey() override;
	void Update(float deltaTime) override;
	float GetDistanceToPlayer() override;
	void Init(const float2& pos, Tilemap* floors, Tilemap* ladders, Avatar& p);
	static float GetValueFromMonkeyFunction(float t, bool positive);
	CollisionChecker* GetCollisionChecker() const;
	Timer* GetHitTimer() const;
	Timer* GetThrowTimer() const;
	void SetHeading(bool _heading);
	bool GetHeading() const;

private:
	MonkeyState* currentState = nullptr;
	Timer* hitTimer = nullptr;
	Timer* throwTimer = nullptr;
	const float DISTANCE_TO_PLAYER=15;
	const int DAMAGE=10;
	CollisionChecker* colCheck = nullptr;
	Box throwCollider;
	const float2 minThrow = { 25,-DISTANCE_TO_PLAYER };
	const float2 maxhrow = { 100,DISTANCE_TO_PLAYER };
	bool headingRight = true;

	
};
