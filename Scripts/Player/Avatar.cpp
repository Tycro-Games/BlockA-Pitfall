#include "precomp.h"
#include "Avatar.h"


Avatar::Avatar(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, Array<Rope>& _ropes,
               Array<Zipline>& _ziplines, Array<ElasticPlant>& _elasticPlants, Array<Coin>& _coins,
               Array<Checkpoint>& _checkpoints, Camera& _cam) :
	saveLoad(""), currentState(nullptr)
{
	cam = &_cam;

	climbTimer = new Timer();
	jumpTimer = new Timer();
	hitJumpTimer = new Timer();

	subject = new Subject();

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	col = new CollisionChecker(&pos, &_floors, &_ladders);
	col->SetNonTiles(_ziplines, _ropes, _elasticPlants, _coins, _checkpoints);

	spawnRocks = new SpawnRocks(*col);
}


Avatar::~Avatar()
{
	delete col;
	delete climbTimer;
	delete jumpTimer;
	delete subject;
	delete hitJumpTimer;

	delete sprite;
	delete currentState;
	delete spawnRocks;
}

//void Avatar::GetFlippedPath(const char* spritePath, char*& spriteFlippedPath)
//{
//	//answer from https://stackoverflow.com/questions/10279718/append-char-to-string-in-c
//	const size_t length = strlen(spritePath);
//	spriteFlippedPath = new char[length + 2];
//	strcpy(spriteFlippedPath, spritePath);
//	const char* c = strchr(spritePath, '.');
//
//	spriteFlippedPath[length - strlen(c)] = 'f';
//	strcpy(spriteFlippedPath + length - strlen(c) + 1, c);
//}

void Avatar::SetStartPosition()
{
	pos.x = Camera::GetPosition().x + Camera::resX / 2;
	pos.y = Camera::GetPosition().y + Camera::resY / 2;
	velocity = 0;
	flipX = -1;
	canMove = true;
	alreadyShot = false;
}

void Avatar::Init()
{
	//setting to world position
	SetStartPosition();
	delete currentState;
	currentState = new FreemovingState();
	currentState->OnEnter(*this);
	canMove = true;
}


void Avatar::Render(Surface* screen)
{
	//convert to screen position
	const float2 camPos = Camera::GetPosition();
	const int x = static_cast<int>(pos.x - PLAYER_OFFSET_X - camPos.x);
	const int y = static_cast<int>(pos.y - PLAYER_OFFSET_Y - camPos.y);
	int directionToLook;
	if (velocity.x > 0.1f)
		directionToLook = 1;
	else if ((velocity.x) < -0.1f)
	{
		directionToLook = -1;
	}
	else
		directionToLook = 0;
	if (directionToLook)
	{
		flipX = -directionToLook;
	}

	if (flipX > 0)
		sprite->DrawFlippedX(screen, x, y);
	else
	{
		sprite->Draw(screen, x, y);
	}
	spawnRocks->Render(screen);

	//source for debug https://stackoverflow.com/questions/1611410/how-to-check-if-a-app-is-in-debug-or-release

#ifdef _DEBUG

	// box
	const uint c = 255 << 16;
	//on screen positions
	const float debugX = pos.x - camPos.x;
	const float debugY = pos.y - camPos.y;

	Box a = AABB::At({debugX, debugY}, *col->GetBoxCollider());
	screen->Box(
		static_cast<int>(a.min.x),
		static_cast<int>(a.min.y),
		static_cast<int>(a.max.x),
		static_cast<int>(a.max.y),
		c);
	//circle
	Box ci = AABB::At({debugX, debugY}, *col->GetFloorCollider());
	screen->Box(
		static_cast<int>(ci.min.x),
		static_cast<int>(ci.min.y),
		static_cast<int>(ci.max.x),
		static_cast<int>(ci.max.y), c);
	Box fl = AABB::At({debugX, debugY}, *col->GetJumpCollider());
	screen->Box(
		static_cast<int>(fl.min.x),
		static_cast<int>(fl.min.y),
		static_cast<int>(fl.max.x),
		static_cast<int>(fl.max.y), c);


#endif
}

void Avatar::SetInput(int2 _input)
{
	input.arrowKeys = _input;
}


void Avatar::UpdateCurrentState(float deltaTime)
{
	PlayerState* newState = currentState->Update(deltaTime);

	if (newState != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = newState;
		currentState->OnEnter(*this);
	}
}

void Avatar::ResetInput()
{
	input.arrowKeys = 0;
	input.shooting = false;
	input.jumping = false;
	input.smallJump = false;
}

void Avatar::Update(float deltaTime)
{
	if (!canMove)
	{
		ResetInput();
	}
	UpdateCurrentState(deltaTime);
	spawnRocks->Update(deltaTime);
	col->IsCollidingCoins();
	col->IsCollidingCheckpoints();
	ResetInput();


	cam->UpdatePosition(deltaTime, col->GetBoxColliderPos(), static_cast<float>(flipX));
}

bool Avatar::IsClimbTimerFinished(float time) const
{
	return climbTimer->elapsed() >= time;
}

void Avatar::SetJumpInput(bool jumpInput)
{
	if (jumpInput)
	{
		if (startedJump == false)
		{
			startedJump = true;
			jumpTimer->reset();
		}
		else if (jumpTimer->elapsed() > SMALL_JUMP_END && !alreadyJumped)
		{
			startedJump = false;
			input.jumping = true;
			alreadyJumped = true;
			jumpTimer->reset();
		}
	}
	else
	{
		if (startedJump)
		{
			if (jumpTimer->elapsed() <= SMALL_JUMP_END)
			{
				input.smallJump = true;
			}
		}
		startedJump = false;
		alreadyJumped = false;
		jumpTimer->reset();
	}
}

void Avatar::SetShootInput(bool shootInput)
{
	if (!alreadyShot)
	{
		input.shooting = shootInput;
		alreadyShot = true;
	}
	if (!shootInput)
		alreadyShot = false;
}

float2 Avatar::GetPos() const
{
	return pos;
}


float2* Avatar::pGetPos()
{
	return &pos;
}

void Avatar::ResetClimbTimer() const
{
	climbTimer->reset();
}

float2 Avatar::GetVelocity() const
{
	return velocity;
}

float2* Avatar::pGetVelocity()
{
	return &velocity;
}

void Avatar::SetVelocity(const float2& _velocity)
{
	velocity = _velocity;
}

void Avatar::SetVelocityX(float x)
{
	velocity.x = x;
}

void Avatar::SetVelocityY(float y)
{
	velocity.y = y;
}

void Avatar::SetPosition(const float2& _pos)
{
	pos = _pos;
}

void Avatar::SetPositionX(const float x)
{
	pos.x = x;
}

void Avatar::SetPositionY(const float y)
{
	pos.y = y;
}

void Avatar::TranslatePosition(const float2& _pos)
{
	pos += _pos;
}

float Avatar::GetSpeed() const
{
	return SPEED;
}

CollisionChecker* Avatar::GetCollisionChecker() const
{
	return col;
}

SpawnRocks* Avatar::GetRockSpawner() const
{
	return spawnRocks;
}


Camera* Avatar::GetCamera() const
{
	return cam;
}

Timer* Avatar::GetClimbTimer() const
{
	return climbTimer;
}


const Input& Avatar::GetInput()
{
	if (hitJumpTimer->elapsedF() < COOLDOWN_HIT_JUMP)
	{
		velocity.x = 0;
		input.arrowKeys = 0;
	}
	return input;
}

Subject* Avatar::GetSubject() const
{
	return subject;
}

Array<Rock>& Avatar::GetRocks() const
{
	return spawnRocks->GetActiveRocks();
}

int Avatar::GetFlip() const
{
	return flipX;
}

void Avatar::ThrowRock(const float2& dir)
{
	shootSound.replay();
	spawnRocks->AddRockToActive(dir, col->GetBoxColliderPos() + float2{
		                            -SHOOT_OFFSET_X * static_cast<float>(flipX), SHOOT_OFFSET_Y
	                            });
}


void Avatar::Notify(int context, EVENT ev)
{
	context;
	switch (ev)
	{
	case PLAYER_DEAD:
		canMove = false;
		break;
	case PLAYER_HIT:
		cout << "Show some hit'\n";
		if (context < 0 && hitJumpTimer->elapsedF() > COOLDOWN_HIT_JUMP) //this means to jump
		{
			input.smallJump = true;
			hitJumpTimer->reset();
		}
		hitSound.play();
		break;
	case SAVE_CHECKPOINT:
		saveLoad.SetName(saveX);
		saveLoad.SaveData(pos.x);
		saveLoad.SetName(saveY);
		saveLoad.SaveData(pos.y);
		break;
	default:
		break;
	}
}
