#pragma once
#include "Scripts/Utilities/AABB.h"
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
	Sprite* spriteFlipped;
	const uint NUMBER_FRAMES = 10;
	float2 pos;
	//input
	int2 dir;
	bool flipX = false;
	const float speed = 250.5f;
	//collider
	AABB aabb;
	const float2 minCollider{ 15,15 }, maxCollider{ 15,15 };
};

