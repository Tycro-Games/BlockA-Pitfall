#pragma once

class MonkeyToGroundState : public MonkeyState
{
public:
	void OnEnter() override;
	void OnExit() override;
	~MonkeyToGroundState() override;
	MonkeyState* Update(Monkey* monkey, float deltaTime) override;
private:
	const float FALL_SPEED = 20.0f;
};
