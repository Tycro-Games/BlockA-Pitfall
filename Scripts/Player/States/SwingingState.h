#pragma once

class SwingingState :public PlayerState
{
public:
	void OnEnter(Avatar& p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;
	void pSetRope(float2* p);

private:
	float2* ropePoint = 0;

	const float SWINGING_JUMP_SPEED = 1.5f;

};

