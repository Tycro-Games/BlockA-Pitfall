#pragma once
#include "Scripts/Tilemap/Tilemap.h"
class Camera;
class Tilemap;

class Avatar
{
public:
	Avatar();
	~Avatar();
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _tilemap, Camera& _cam);
	void Render(Surface* screen);
	void GetInput(int2 input);
	void Update(float deltaTime);
	void Jump();
	float2 GetPos();
private:
	Sprite* sprite;
	Sprite* spriteFlipped;
	Tilemap* tilemap;
	Camera* cam;
	float2 velocity;
	const uint NUMBER_FRAMES = 10;
	float2 pos;
	const float GRAVITY = 9.8f;
	//input
	int2 dir;
	const float2 EGDGE_OFFSET = 15.0f;

	bool flipX = false;
	const float speed = 250.5f;
	//collider
	AABB boxCollider;
	AABB circleCollider;
	const float2 minCollider{ -15,-15 }, maxCollider{ 15,15 };
};

