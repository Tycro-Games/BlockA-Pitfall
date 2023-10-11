#pragma once

class BoarState;

class Boar : public Enemy
{
public:
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	~Boar() override;
	bool AtackPlayer();
	void Init(const float2& _a, const float2& _b, Avatar& _avatar);
	const float2& GetDesiredPos() const;
	const float2& GetStartPos() const;
	const float2& GetEndPos() const;
	void SwitchPositions();
	void SetDesiredPos(const float2& _desiredPos);
	float GetDistanceToPlayer() override;
	Timer* GetHitTimer() const;

private:
	Timer* hitRecently=nullptr;
	BoarState* currentState = nullptr;
	float2 desiredPos = 0;
	float2 pointA = 0;
	float2 pointB = 0;
	bool turn = false;
	const float DISTANCE_TO_PLAYER = 30.0f;
	const uint DAMAGE = 10;
};
