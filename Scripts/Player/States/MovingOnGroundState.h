#pragma once

class MovingOnGroundState :public State
{
public:
	// Inherited via State
	void OnEnter(Avatar& p) override;
	
	State* Update(Avatar& player, Input input, float deltaTime) override;
	void OnExit() override;
private:
	
	const float2 FLOOR_POS = { 9.5f,30.0f };
	const float JUMP_FORCE = 3.0f;

};

