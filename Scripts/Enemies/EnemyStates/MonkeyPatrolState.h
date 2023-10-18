#pragma once

class MonkeyPatrolState : public MonkeyState
{
public:
	~MonkeyPatrolState() override;
	void SetSpeedModifier();
	void OnEnter() override;
	MonkeyState* ToTurnState() const;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
	void SetDesiredPosition(float x);
	void SetOriginalPosition(const float2& pos);

private:
	float2 originalPosition = 0;
	float2 desiredPos = 0;
	float currentOffset = 0;
	float DISTANCE_TO_NEXT_POSITION = 1000.0f;
	float MIN_TO_NEXT_POSITION = 50.0f;
	float SPEED_TIME = 0.9f;
	float SPEED_MODIFIER = 0;
	const float MIN_SPEED = 0.2f;
	const float HIT_TIME_COOLDOWN = 1.50f;
	const float THROW_COOLDOWN = 2.75f;
};
