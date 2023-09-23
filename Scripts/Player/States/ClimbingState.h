#pragma once
class ClimbingState : State
{
	// Inherited via State
	void OnEnter() override;
	State* Update(Avatar& player, Input input, float deltaTime) override;
	void OnExit() override;
};

