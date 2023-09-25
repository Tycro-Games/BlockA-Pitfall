#pragma once


class State;
struct Timer;

struct Input {
	int2 arrowKeys = { 0 };
	bool jumping = false;
};
class Avatar
{

public:
	Avatar();
	~Avatar();
	//TODO add to a general sprite class
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _tilemap, Tilemap& _ropes, Camera& _cam);
	void Render(Surface* screen);
	void Update(float deltaTime);
	void SetJumpInput(bool jumpInput);
	void SetInput(int2 input);
	float2 GetPos() const;
	float2* pGetPos();

	float2 GetVelocity() const;
	float2* pGetVelocity();
	void SetVelocity(float2 velocity);

	float GetSpeed() const;
	Tilemap* GetFloors() const;
	Tilemap* GetLadders() const;
	Camera* GetCamera()const;
	Timer* GetClimbTimer() const;
	Box* GetFloorCollider();
	Box* GetBoxCollider();
	Input* pGetInput();

private:
	Input input;
	void SnapToFloor(float deltaTime, float2& floorPos);
	void SetState(float2 floorPos);
	void UpdateCurrentState(float deltaTime);

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

	State* currentState;


	//physics
	float2 velocity = 0;
	float2 pos = 0;
	const float2 CAMERA_OFFSET = { 100 ,-50 };
	const float GRAVITY = 9.8f;
	const float JUMP_FORCE = 3.0f;
	const float CLIMBING_JUMP_FORCE = 2.5f;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	bool canJump = false;
	int flipX = -1;
	Timer* climbTimer;
	const float climbDelay = 0.5f;
	//input
	int2 dir;

	//collider
	const float BOX_SIZE = 4.0f;
	const float2 BOX_POS = { 9.0f,15.0f };
	Box boxCollider;

	const float FLOOR_SIZE = 8.0f;
	Box floorCollider;
	const float2 FLOOR_POS = { 9.5f,30.0f };
	const float2 PLAYER_OFFSET = { 15.0f,-7.0f };

	//animation

};

