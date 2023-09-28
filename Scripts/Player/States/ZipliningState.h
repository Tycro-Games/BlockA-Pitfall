#pragma once

class ZipliningState : public PlayerState
{
public:
	void OnEnter(Avatar& p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;
	void SetZiplineEnd(float2 end);
	void SetZiplineStart(float2 start);

private:
	float distance = 0;
	float maxVelocity = 2.7f;
	float2 ziplineEnd = 0;
	float2 ziplineStart = 0;
	float2 direction = 0;
	const float MAX_SPEED = 300.0f;

	const float ZIPLINE_JUMP_SPEED = 1.0f;

	float originalLeng = 0;;
	float wholeLeng = 0;;
};
