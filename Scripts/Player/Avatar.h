#pragma once
#include "Scripts/Tilemap/Tilemap.h"
#include "Scripts/Utilities/AABB.h"

class Camera;

class Avatar
{
public:
	Avatar();
	~Avatar();
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _tilemap, Tilemap& ropes, Camera& _cam);
	void Render(Surface* screen);
	void GetInput(int2 input);
	void SnapToFloor(float deltaTime, float2& floorPos);
	void Update(float deltaTime);
	void Jump();
	float2 GetPos() const;
	const float2* GetPos();

private:
	enum playerState
	{
		FREEMOVE,
		LADDER,
		COUNT
	}state;
	//base for general sprite class and render
	Sprite* sprite;
	Sprite* spriteFlipped;
	//components
	Tilemap* floors;
	Tilemap* ladders;
	Camera* cam;


	//physics
	float2 velocity, pos;
	const float2 CAMERA_OFFSET = { 100 ,0 };
	const float GRAVITY = 9.8f;
	const float JUMP_FORCE = 4.0f;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	int lastTileColumn;
	bool onFloor = false;
	short int flipX = false;

	//input
	int2 dir;
	bool jumping = false;

	//collider
	const float BOX_SIZE = 8.0f;
	const float2 BOX_POS = { 9.0f,5.0f };
	Box boxCollider;

	const float FLOOR_SIZE = 8.0f;
	const float2 FLOOR_POS = { 9.5f,20.0f };
	Box floorCollider;
	const float2 PLAYER_OFFSET = { 12.0f,3.0f };

	//animation

};

