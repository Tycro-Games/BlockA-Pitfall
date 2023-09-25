#pragma once
class ClimbingState : public State
{
public:

	// Inherited via State
	void OnEnter(Avatar& p) override;
	State* Update(Avatar& player, float deltaTime) override;
	void OnExit() override;
private:
	const float CLIMBING_JUMP_FORCE = 2.5f;
	Timer* climbTimer = nullptr;

};

