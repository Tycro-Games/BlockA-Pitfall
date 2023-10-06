#pragma once

class MonkeyBall: public Enemy
{
public:
	void UpdateVelocity();
	MonkeyBall(Subject* s, Monkey* _monkey, Avatar* p, const float2& _startPos);
	~MonkeyBall();
	float KinematicEquation(float a, float v, float p, float t);
	static float GetVelocity(float pI, float pF, float t);
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	float GetDistanceToPlayer() override;

private:
	float2 dir;
	float2 fPos;
	float2 sPos;
	float2 velocity = 0;
	const float DISTANCE_TO_PLAYER = 14.0f;
	Monkey* monkey = nullptr;
	float speed = 0;
	float timeToReach = 3.3f;
	const int DG = 10;
	float t = 0;
};
