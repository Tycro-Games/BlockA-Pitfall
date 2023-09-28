#pragma once
class ClimbingState : public PlayerState
{
public:

	void OnEnter(Avatar& p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;
protected:
private:


	const float CLIMBING_JUMP_FORCE = 1.4f;

};

