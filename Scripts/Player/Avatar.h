#pragma once


class Rope;
class Zipline;
class State;
struct Timer;

struct Input {
	int2 arrowKeys = { 0 };
	bool jumping = false;
	bool smallJump = false;
};
class Avatar
{

public:
	Avatar();
	~Avatar();
	//TODO add to a general sprite class
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, Rope* _ropes, size_t _ropeCount, Zipline* _ziplines, size_t
		_ziplineCount, Camera& _cam);
	void Render(Surface* screen);
	void Update(float deltaTime);
	bool IsCollidingLadders(float2& floorPos) const;
	bool IsCollidingRopes(float2*& pMovingPart) const;
	bool IsCollidingZiplines(float2& _normal, float2& _start, float2& _end);
	bool IsClimbTimerFinished(float time) const;
	void SetJumpInput(bool jumpInput);
	void SetInput(int2 input);
	float2 GetPos() const;
	float2 GetBoxColliderPos() const;
	float2 GetBoxColliderOffset() const;
	float2* pGetPos();
	void ResetClimbTimer();
	float2 GetVelocity() const;
	float2* pGetVelocity();
	void SetVelocity(const float2& _velocity);

	void SetPostion(const float2& _pos);
	void TransaltePosition(const float2& _pos);
	float GetSpeed() const;
	Tilemap* GetFloors() const;
	Tilemap* GetLadders() const;
	Rope* GetRopes() const;
	Zipline* GetZiplines() const;
	size_t GetZiplinesCount() const;
	size_t GetRopeCount() const;
	Camera* GetCamera()const;
	Timer* GetClimbTimer() const;
	Box* GetFloorCollider();
	Box* GetBoxCollider();
	Input* pGetInput();
	float2 getFloorPos();

private:
	Input input;
	Timer* climbTimer = nullptr;
	bool startedJump = false;
	bool alreadyJumped = false;
	Timer* jumpTimer = nullptr;
	const float SMALL_JUMP_END = 0.02f;
	void UpdateCurrentState(float deltaTime);

	//base for general sprite class and render
	Sprite* sprite;
	Sprite* spriteFlipped;
	//components
	Tilemap* floors;
	Tilemap* ladders;
	Zipline* ziplines;
	Rope* ropes;
	Camera* cam;
	size_t ropeCount = 0;
	size_t ziplineCount = 0;
	State* currentState;


	//physics
	float2 velocity = 0;
	float2 pos = 0;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	int flipX = -1;

	//colliders
	const float BOX_SIZE = 4.0f;
	const float2 BOX_POS = { 9.0f,15.0f };
	Box boxCollider;

	const float FLOOR_SIZE = 8.0f;
	Box floorCollider;
	const float2 FLOOR_POS = { 9.5f,30.0f };
	const float2 PLAYER_OFFSET = { 15.0f,-7.0f };

	//ziplines and ropes
	const float RADIUS_TO_ZIPLINE = 10.0f;
	const float RADIUS_TO_ROPE = 30.0f;
	const float ZIPLINE_OFFSET_END = 25.0f;

	//animation

};

