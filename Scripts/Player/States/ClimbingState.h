#pragma once
class ClimbingState : public State
{
public:

	void OnEnter(Avatar& p) override;
	State* Update( float deltaTime) override;
	void OnExit() override;
protected:
	void SetVariables(Avatar& p) override;
private:
	Timer* climbTimer = nullptr;
	Input* input = nullptr;
	float2* pos = nullptr;
	float2* velocity = nullptr;
	Tilemap* floors = nullptr;
	Tilemap* ladders = nullptr;
	Camera* cam = nullptr;
	Box* floorCollider = nullptr;
	Box* boxCollider = nullptr;
	float speed = 0;
	const float CLIMBING_JUMP_FORCE = 2.5f;

};

