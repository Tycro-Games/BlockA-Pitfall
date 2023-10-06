#pragma once

class MonkeyThrowState : public MonkeyState
{
public:
	~MonkeyThrowState() override;
	void OnEnter() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
private:
	Timer* stopTimer = nullptr;
	const float TIME_TO_THROW = .7f;
	const float MIN_VALUE = 0.2f;
};
