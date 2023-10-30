#pragma once

class BoarState;

class Boar : public Enemy
{
public:
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	~Boar() override;
	Boar();
	bool AtackPlayer() const;
	void Init(const float2& _a, const float2& _b, Avatar& _avatar);
	const float2& GetDesiredPos() const;
	const float2& GetStartPos() const;
	const float2& GetEndPos() const;
	void SwitchPositions();
	void SetDesiredPos(const float2& _desiredPos);
	float GetDistanceToPlayer() override;
	Timer* GetHitTimer() const;
	void Dead() override;

private:
	Timer* hitRecently = nullptr;
	BoarState* currentState = nullptr;

	const int RESIZE = 60;
	const int FRAMES = 4;
	float2 desiredPos = 0;
	float2 pointA = 0;
	float2 pointB = 0;
	bool turn = false;
	const float DISTANCE_TO_PLAYER = 30.0f;
	const uint DAMAGE = 10;
	const int BOAR_POINTS = 50;
	const int HP = 40;
	const char* saveName = "Boar";
	bool headingRight = false;

	Sprite* boarSprite = nullptr;
	Sprite* preRendered = nullptr;
	Sprite* boarSurface_ = nullptr;
};
