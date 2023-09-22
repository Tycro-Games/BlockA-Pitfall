#pragma once
class FreemovingState : State
{
	// Inherited via State
	void OnEnter() override;
	void Update(Avatar& player, Input input, float deltaTime) override;
	void SnapToFloor(Avatar& player, float deltaTime);
	void OnExit() override;
};

