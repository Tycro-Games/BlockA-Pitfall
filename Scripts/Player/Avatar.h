#pragma once


class Rope;
class Zipline;
class PlayerState;
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
	bool IsCollidingLadders(const Box& col, float2& floorPos) const;
	bool IsCollidingLadders(const float2& newPos, const Box& col) const;
	bool IsCollidingLadders(const Box& col) const;
	bool IsCollidingFloors(const float2& newPos, const Box& col) const;
	bool IsCollidingFloors(const Box& col) const;
	bool IsCollidingFloors(const Box& col, float2& floorPos) const;

	bool IsCollidingRopes(float2*& pMovingPart) const;
	bool IsCollidingZiplines(float2& _normal, float2& _start, float2& _end) const;
	bool IsClimbTimerFinished(float time) const;
	void SetJumpInput(bool jumpInput);
	void SetInput(int2 input);
	float2 GetPos() const;
	float2 GetBoxColliderPos() const;
	float2 GetBoxColliderOffset() const;
	float2* pGetPos();
	void ResetClimbTimer() const;
	float2 GetVelocity() const;
	float2* pGetVelocity();
	void SetVelocity(const float2& _velocity);
	void SetVelocityX(float x);
	void SetVelocityY(float y);

	void SetPosition(const float2& _pos);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void TranslatePosition(const float2& _pos);
	float GetSpeed() const;
	Tilemap* GetFloors() const;
	Tilemap* GetLadders() const;
	Rope* GetRopes() const;
	Zipline* GetZiplines() const;
	size_t GetZiplinesCount() const;
	size_t GetRopeCount() const;
	Camera* GetCamera()const;
	Timer* GetClimbTimer() const;
	const Box& GetFloorCollider() const;
	const Box& GetBoxCollider() const;
	const Box& GetJumpCollider() const;
	const Input& GetInput() const;
	float2 GetFloorPos() const;
	float2 GetJumpPos() const;

private:
	Input input;
	Timer* climbTimer = nullptr;
	bool startedJump = false;
	bool alreadyJumped = false;
	Timer* jumpTimer = nullptr;
	const float SMALL_JUMP_END = 0.2f;
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
	PlayerState* currentState;


	//physics
	float2 velocity = 0;
	float2 pos = 0;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	int flipX = -1;

	//colliders
	const float BOX_SIZE = 5.0f;
	const float2 BOX_POS = { 9.0f,17.0f };
	Box boxCollider;

	const float FLOOR_SIZE = 8.0f;
	Box floorCollider;
	const float2 FLOOR_POS = { 9.5f,30.0f };
	const float2 PLAYER_OFFSET = { 15.0f,-7.0f };

	Box jumpCollider;
	const float2 JUMP_POS = { 9.5f,42.0f };
	const float JUMP_SIZE_X = 8.0f;
	const float JUMP_SIZE_Y = 4.0f;

	//ziplines and ropes
	const float RADIUS_TO_ZIPLINE = 25.0f;
	const float RADIUS_TO_ROPE = 30.0f;
	const float ZIPLINE_OFFSET_END = 25.0f;

	//animation

};

