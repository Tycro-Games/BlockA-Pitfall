#pragma once
#include "Scripts/Tilemap/Tilemap.h"
#include "Scripts/Utilities/AABB.h"

class Camera;

class Avatar
{
public:
	Avatar();
	~Avatar();
	//TODO add to a general sprite class
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _tilemap, Tilemap& _ropes, Camera& _cam);
	void Render(Surface* screen);
	void GetInput(int2 input);
	void Update(float deltaTime);
	void Jump();
	float2 GetPos() const;

private:
	void SnapToFloor(float deltaTime, float2& floorPos);
	void SetState(float2 floorPos);

	enum playerState
	{
		FREEMOVE,
		CLIMBPING,
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
	const float JUMP_FORCE = 3.0f;
	const float CLIMBING_JUMP_FORCE = 2.5f;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	bool canJump = false;
	short int flipX = false;
	Timer climbTimer;
	const float climbDelay = 0.5f;
	//input
	int2 dir;

	//collider
	const float BOX_SIZE = 8.0f;
	const float2 BOX_POS = { 9.0f,5.0f };
	Box boxCollider;

	const float FLOOR_SIZE = 8.0f;
	Box floorCollider;
	const float2 FLOOR_POS = { 9.5f,20.0f };
	const float2 PLAYER_OFFSET = { 12.0f,3.0f };

	//animation

};

