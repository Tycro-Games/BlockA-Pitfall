#pragma once
#include "Scripts/Utilities/Array.h"


class Rope;
class Zipline;
class PlayerState;
struct Timer;

//struct ColliderDimensions
//{
//	float BOX_SIZE = 5.0f;
//	float2 BOX_POS = { 9.0f, 17.0f };
//	Box col;
//	ColliderDimensions(float size, const float2& pos, const Box& b)
//	{
//		BOX_SIZE = size;
//		BOX_POS = pos;
//		col = b;
//	}
//};
struct Input {
	int2 arrowKeys = { 0 };
	bool jumping = false;
	bool smallJump = false;
};
class Avatar : public Observer, public Entity
{

public:
	Avatar();
	~Avatar() override;
	//observer
	void Notify(int context, EVENT ev) override;
	//TODO add to a general sprite class
	void GetFlippedPath(const char* spritePath, char*& spriteFlippedPath);
	void Init(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, Array<Rope>& _ropes, Array<Zipline>& _ziplines, Array<
	          ElasticPlant>& _elasticPlants, Camera& _cam);
	//entity
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;


	bool IsClimbTimerFinished(float time) const;
	void ResetClimbTimer() const;

	void SetJumpInput(bool jumpInput);
	void SetInput(int2 input);

	float2 GetPos() const;

	float2* pGetPos();
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

	CollisionChecker* GetCollisionChecker()const;
	Camera* GetCamera()const;
	Timer* GetClimbTimer() const;

	const Input& GetInput() const;
	Subject* GetSubject() const;



private:

	Subject* subject;
	Input input;
	Timer* climbTimer = nullptr;
	bool startedJump = false;
	bool alreadyJumped = false;
	Timer* jumpTimer = nullptr;
	const float SMALL_JUMP_END = 0.13f;
	void UpdateCurrentState(float deltaTime);
	void ResetInput();


	//base for general sprite class and render
	Sprite* sprite;
	Sprite* spriteFlipped;
	//components
	Camera* cam;
	PlayerState* currentState;


	//physics
	float2 velocity = 0;
	float2 pos = 0;
	const float SPEED = 250.5f;
	const uint NUMBER_FRAMES = 10;
	int flipX = -1;

	//colliders
	CollisionChecker* col = nullptr;

	//animation
	const float2 PLAYER_OFFSET = { 15.0f,-7.0f };

	bool canMove = true;
};

