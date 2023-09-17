#pragma once
#include "Scripts/Tilemap/Tilemap.h"

class Camera;

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
	float2 GetPos() const;
	const float2* GetPos();

private:
	//base for general sprite class and render
	Sprite* sprite;
	Sprite* spriteFlipped;
	//components
	Tilemap* tilemap;
	Camera* cam;


	//physics
	float2 velocity, pos;
	const float2 CAMERA_OFFSET = { 100 ,0 };
	const float GRAVITY = 9.8f;
	const float JUMP_FORCE = 5.0f;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;

	bool onFloor = false;
	short int flipX = false;

	//input
	int2 dir;
	bool jumping = false;

	//collider
	AABB boxCollider;
	AABB circleCollider;
	const float2 minCollider{ -16,-16 }, maxCollider{ 16,16 };
	//animation

};

