#pragma once


class Checkpoint;
class Rock;
class SpawnRocks;
class Rope;
class Zipline;
class PlayerState;
struct Timer;

//struct ColliderDimensions
//{
//	float BOX_SIZE = 5.0f;
//	float2 BOX_POS = { 9.0f, 17.0f };
//	Box col;
//	ColliderDimensions(float Size, const float2& pos, const Box& b)
//	{
//		BOX_SIZE = Size;
//		BOX_POS = pos;
//		col = b;
//	}
//};
struct Input
{
	int2 arrowKeys = {0};
	bool shooting = false;
	bool jumping = false;
	bool smallJump = false;
};

class Avatar : public Observer, public Entity
{
public:
	Avatar(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, StaticArray<Rope>& _ropes,
	       StaticArray<Zipline>& _ziplines, StaticArray<ElasticPlant>& _elasticPlants, StaticArray<Coin>& _coins,
	       StaticArray<Checkpoint>& _checkpoints, Camera& _cam);
	~Avatar() override;
	//observer
	void Notify(int context, EVENT ev) override;
	void SetStartPosition();
	void Init();
	//entity
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;

	void PlayJumpSound();
	bool IsClimbTimerFinished(float time) const;
	void ResetClimbTimer() const;

	void SetJumpInput(bool jumpInput);
	void SetShootInput(bool shootInput);
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

	CollisionChecker* GetCollisionChecker() const;
	SpawnRocks* GetRockSpawner() const;
	Camera* GetCamera() const;
	Timer* GetClimbTimer() const;
	const Input& GetInput();


	Subject* GetSubject() const;
	StaticArray<Rock>& GetRocks() const;
	int GetFlip() const;
	void ThrowRock(const float2& dir);

private:
	void UpdateCurrentState(float deltaTime);
	void ResetInput();
	//physics
	Audio::Sound shootSound{"assets/Audio/Laser_Shoot16.wav"};
	Audio::Sound hitSound{"assets/Audio/Hit_Hurt8.wav"};
	Audio::Sound jumpSound{"assets/Audio/Jump5.wav"};

	const float SPEED = 250.5f;
	const float SHOOT_OFFSET_X = {9.0f};
	const float SHOOT_OFFSET_Y = {0.0f};
	const float PLAYER_OFFSET_X = {15.0f};
	const float PLAYER_OFFSET_Y = {-7.0f,};
	const uint NUMBER_FRAMES = 10;
	int flipX = -1;
	bool alreadyJumped = false;

	const float SMALL_JUMP_END = 0.13f;

	Input input;

	bool startedJump = false;

	//saving
	SavingLoading saveLoad;
	const char* saveX = "PlayerX";
	const char* saveY = "PlayerY";


	bool canMove = true;
	bool alreadyShot = false;
	const float COOLDOWN_HIT_JUMP = .07f;
	const float BLIP_INTERVAL = .05f;
	const float BLIP_COOLDOWN = 0.5f;
	bool invisible = false;
	bool firstHit = false;

	//colliders
	CollisionChecker* col = nullptr;
	//rocks
	SpawnRocks* spawnRocks = nullptr;
	//base for general sprite class and render
	Sprite* sprite;
	//components
	Camera* cam;
	PlayerState* currentState;
	Timer* climbTimer = nullptr;
	Subject* subject;
	Timer* jumpTimer = nullptr;
	Timer* hitJumpTimer = nullptr;
	Timer* blipTimer = nullptr;
	Timer* blipCoolDown = nullptr;
	//physics
	uint* dummbyVar = nullptr;
	float2 pos = 0;
	float2 velocity = 0;
};
