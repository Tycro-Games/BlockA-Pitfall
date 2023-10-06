﻿#pragma once

class MonkeyTurnState : public MonkeyState
{
public:
	~MonkeyTurnState() override;
	void OnEnter() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
private:
	Timer* stopTimer = nullptr;
	float timeToTurn = .198f;
	const float MIN_VALUE = 0.3f;
	const float RANDOM_MODIFIER_TIME = 0.4f;

};
