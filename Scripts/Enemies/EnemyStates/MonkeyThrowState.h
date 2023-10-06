#pragma once

class MonkeyBall;

class MonkeyThrowState : public MonkeyState
{
public:
	~MonkeyThrowState() override;
	void OnEnter() override;
	void SpawnBall(Monkey* monkey);
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
private:
	Timer* stopTimer = nullptr;
	const float TIME_TO_THROW = 1.0f;
	const float MIN_VALUE = 0.2f;
};
