#pragma once

class MonkeyTurnState: public MonkeyState
{
public:
	~MonkeyTurnState() override;
	void OnEnter() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
	void OnExit() override;
	void SetHeading(bool _heading);
private:
	Timer* stopTimer = nullptr;
	 float timeToTurn = .378f;
	bool headingRight = false;
	const float MIN_VALUE=0.3f;
	const float RANDOM_MODIFIER_TIME = 1.2f;

};
