#pragma once

class MonkeyBall;

class MonkeyThrowState : public MonkeyState
{
public:
	~MonkeyThrowState() override;
	void OnEnter() override;
	void SpawnBall(Monkey* monkey) const;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;

private:
	Timer* stopTimer = nullptr;
	const float TIME_TO_THROW = .1f;
	const float MIN_VALUE = 0.2f;
	const float MID_POINT_MIN = -30;
	const float MID_POINT_RANDOM = -50;
};
