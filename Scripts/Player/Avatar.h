#pragma once
class Avatar
{
public:
	Avatar();
	~Avatar();
	void Init(const char* spritePath);
	void Render(Surface* screen);
	void Move(int2 input);
	void Update(float deltaTime);
private:
	Sprite* sprite;
	const uint NUMBER_FRAMES = 10;
	float2 pos;
	//input
	int2 dir;
	bool flipX = false;
	const float speed = .5f;
};

