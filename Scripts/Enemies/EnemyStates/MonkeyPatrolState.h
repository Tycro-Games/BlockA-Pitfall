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
	void SetHeading(bool _heading);
private:
	float2 originalPosition = 0;
	float2 desiredPos = 0;
	float currentOffset = 0;
	float DISTANCE_TO_NEXT_POSITION = 600.0f;
	float MIN_TO_NEXT_POSITION = 100.0f;
	float SPEED_TIME = 1.5f;
	float SPEED_MODIFIER = 0;
	bool headingRight = true;
	const float MIN_SPEED = 0.2f;
};
