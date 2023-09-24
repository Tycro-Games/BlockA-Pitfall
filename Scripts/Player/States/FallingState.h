#pragma once

class FallingState : public State
{
public:


	void OnEnter(Avatar& p) override;
	State* Update(Avatar& player, Input input, float deltaTime) override;
	void OnExit() override;

protected:
	void SetVariables(Avatar& p) override;

private:

	const float GRAVITY = 9.8f;
	Timer* climbTimer = nullptr;
	const float CLIMB_DELAY = 0.5f;
};
