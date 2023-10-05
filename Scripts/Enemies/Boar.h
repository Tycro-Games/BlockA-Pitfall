#pragma once

class BoarState;

class Boar : public Enemy
{
public:
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	~Boar() override;
	void Init(const float2& _a, const float2& _b, Avatar& _avatar);
	const float2& GetDesiredPos() const;
	void SetDesiredPos(const float2& _desiredPos);
	float GetDistanceToPlayer() override;

private:
	BoarState* currentState = nullptr;
	float2 desiredPos = 0;
	float2 pointA = 0;
	float2 pointB = 0;


	const float DISTANCE_TO_PLAYER = 30.0f;
	const int DAMAGE = 10;
};
