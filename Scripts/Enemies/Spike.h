#pragma once
class Spike : public Enemy
{
public:
	void Init(const float2& _position, Avatar* avatar);
	void Update(float deltaTime) override;
	~Spike() override;

private:
	const float DISTANCE_TO_PLAYER=50.0f;
	const int DAMAGE = 5.0f;
};

