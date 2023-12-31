﻿#pragma once

class MonkeyOnLadderState : public MonkeyState
{
public:
	~MonkeyOnLadderState() override;
	void RandomTime();
	void OnEnter() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;

private:
	const float2 END_POS_RELATIVE = float2{100, 200};
	const float2 RANDOM_OFFSET = float2{20, 0};
	Timer* stopTimer = nullptr;

	const float TIME_TO_THROW = 1.6f;
	const float VARIABLE_TIME = .9f;
	float randomTime = 0;

	const float SPEED = 2.5f;
};
