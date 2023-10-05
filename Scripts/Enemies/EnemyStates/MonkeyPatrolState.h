#pragma once

class MonkeyPatrolState : public MonkeyState
{
public:
	~MonkeyPatrolState() override;
	void OnEnter() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
	void SetDesiredPosition(float x);
	void SetOriginalPosition(const float2& pos);
private:
	float2 originalPosition = 0;
	float2 desiredPos = 0;
	float currentOffset = 0;
	float DISTANCE_TO_NEXT_POSITION = 270.0f;
	float SPEED_TIME = 6.5f;
};
