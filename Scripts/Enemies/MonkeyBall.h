#pragma once

class MonkeyBall: public Enemy
{
public:
	void UpdatePosition();
	MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos);
	~MonkeyBall();
	float KinematicEquation(float a, float v, float p, float t);
	static float GetVelocity(float pI, float pF, float t);
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
	float SPEED = 3.0f;
	float timeToReach = 1.5f;
	const int DG = 10;
	float t = 0;
	const float MID_POINT_MIN = -30;
	const float MID_POINT_RANDOM = -50;
	const float GRAVITY = 9.8f;
};
