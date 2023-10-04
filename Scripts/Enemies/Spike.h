#pragma once
class Spike : public Enemy
{
public:
	void Init(const float2& _position, Avatar* avatar);
	void Update(float deltaTime) override;
	~Spike() override;
	void Render(Surface* screen) override;

private:
	const float DISTANCE_TO_PLAYER=20.0f;
	const int DAMAGE = 5.0f;
	int x1=0;
	int x2=0;
	int y1=0;
	int y2=0;
	Box col;
	bool onScreen = false;
};

