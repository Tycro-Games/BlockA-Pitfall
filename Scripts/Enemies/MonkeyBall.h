#pragma once

class MonkeyBall : public Enemy
{
public:
	MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos, const float2& _midPos,
	           const float2& _finalPos, float _speed = 3.0f);


	~MonkeyBall() override;
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	float GetDistanceToPlayer() override;

private:
	float2 newPos;
	float2 finalPos;
	float2 startPos;
	float2 midPos;
	float2 velocity = 0;
	const float DISTANCE_TO_PLAYER = 7.0f;
	Monkey* monkey = nullptr;
	float speed = 3.0f;
	float timeToReach = 1.5f;
	const int DG = 10;
	float t = 0;
	const float GRAVITY = 9.8f;
};
