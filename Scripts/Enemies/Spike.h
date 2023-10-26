#pragma once
class Spike : public Enemy
{
public:
	void Init(const float2& _position, Avatar& _avatar);
	void Update(float deltaTime) override;
	~Spike() override;
	Spike();
	void Render(Surface* screen) override;
	float GetDistanceToPlayer() override;

private:
	inline static Sprite* sprite = nullptr;
	const float DISTANCE_TO_PLAYER = 18.0f;
	const int DAMAGE = 10;
	const int SIZE_X = 32;
	const int SIZE_Y = 32;
};
