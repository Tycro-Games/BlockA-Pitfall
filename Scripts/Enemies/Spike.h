#pragma once
class Spike : public Enemy
{
public:
	void Init(const float2& _position, Avatar& _avatar);
	void Update(float deltaTime) override;
	~Spike() override;
	void Render(Surface* screen) override;
	float GetDistanceToPlayer() override;

private:
	const float DISTANCE_TO_PLAYER = 20.0f;
	const int DAMAGE = 5;
};
