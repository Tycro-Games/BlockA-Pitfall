#include "precomp.h"
#include "Avatar.h"




Avatar::Avatar() : sprite(nullptr), spriteFlipped(nullptr), floors(nullptr), ladders(nullptr), ziplines(nullptr),
ropes(nullptr),
cam(nullptr),
currentState(nullptr),
velocity(),
pos(), dir()
{
	climbTimer = new Timer();
}

Avatar::~Avatar()
{
	delete climbTimer;
	delete sprite;
	delete spriteFlipped;
	delete currentState;

}

void Avatar::GetFlippedPath(const char* spritePath, char*& spriteFlippedPath)
{
	//answer from https://stackoverflow.com/questions/10279718/append-char-to-string-in-c
	const size_t length = strlen(spritePath);
	spriteFlippedPath = new char[length + 2];
	strcpy(spriteFlippedPath, spritePath);
	const char* c = strchr(spritePath, '.');

	spriteFlippedPath[length - strlen(c)] = 'f';
	strcpy(spriteFlippedPath + length - strlen(c) + 1, c);
}

void Avatar::Init(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, Rope* _ropes, size_t _ropeCount, Zipline* _ziplines, size_t _ziplineCount, Camera& _cam)
{
	floors = &_floors;
	ladders = &_ladders;
	ropes = _ropes;
	ziplines = _ziplines;
	cam = &_cam;
	ropeCount = _ropeCount;
	ziplineCount = _ziplineCount;
	char* spriteFlippedPath;
	GetFlippedPath(spritePath, spriteFlippedPath);

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	spriteFlipped = new Sprite(new Surface(spriteFlippedPath), NUMBER_FRAMES);
	//setting to world position
	pos.x = Camera::GetPosition().x + SCRWIDTH / 2;
	pos.y = Camera::GetPosition().y + SCRHEIGHT / 2;
	floorCollider = Box{ FLOOR_POS - FLOOR_SIZE,FLOOR_POS + FLOOR_SIZE };
	boxCollider = Box{ BOX_POS - BOX_SIZE,BOX_POS + BOX_SIZE };
	currentState = new FreemovingState();
	currentState->OnEnter(*this);
	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	//convert to screen position
	const float2 camPos = cam->GetPosition();
	const int x = static_cast<int>(pos.x - PLAYER_OFFSET.x - camPos.x);
	const int y = static_cast<int>(pos.y - PLAYER_OFFSET.y - camPos.y);
	int i = 1;
	if ((velocity.x) > 0.1f)
		i = 1;
	else if ((velocity.x) < -0.1f)
	{
		i = -1;
	}
	else
		i = 0;
	if (i) {
		flipX = -i;
	}

	if (flipX > 0)
		spriteFlipped->Draw(screen, x, y);
	else
	{
		sprite->Draw(screen, x, y);

	}
	//source for debug https://stackoverflow.com/questions/1611410/how-to-check-if-a-app-is-in-debug-or-release

#ifdef _DEBUG

	// box
	const uint c = 255 << 16;
	//on screen positions
	const float debugX = pos.x - camPos.x;
	const float debugY = pos.y - camPos.y;

	Box a = AABB::At({ debugX, debugY }, boxCollider);
	screen->Box(
		static_cast<int>(a.min.x),
		static_cast<int>(a.min.y),
		static_cast<int>(a.max.x),
		static_cast<int>(a.max.y),
		c);
	//circle
	Box ci = AABB::At({ debugX, debugY }, floorCollider);
	screen->Box(
		static_cast<int>(ci.min.x),
		static_cast<int>(ci.min.y),
		static_cast<int>(ci.max.x),
		static_cast<int>(ci.max.y), c);


#endif

}

void Avatar::SetInput(int2 _input)
{
	input.arrowKeys = _input;
	dir = (_input);
}


void Avatar::UpdateCurrentState(float deltaTime)
{
	State* newState = currentState->Update(deltaTime);
	if (newState != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = newState;
		currentState->OnEnter(*this);
	}
}

void Avatar::Update(float deltaTime)
{
	UpdateCurrentState(deltaTime);
	input.jumping = false;

	cam->UpdatePosition(deltaTime, GetBoxColliderPos(), float2{ CAMERA_OFFSET.x * static_cast<float>(flipX),
		CAMERA_OFFSET.y });
}


void Avatar::SetJumpInput(bool jumpInput)
{
	input.jumping = jumpInput;
}

float2 Avatar::GetPos() const
{
	return pos;
}

float2 Avatar::GetBoxColliderPos() const
{
	return pos + BOX_POS;
}
float2 Avatar::GetBoxColliderOffset() const
{
	return  BOX_POS;
}

float2* Avatar::pGetPos()
{
	return &pos;
}

float2 Avatar::GetVelocity() const
{
	return velocity;
}

float2* Avatar::pGetVelocity()
{
	return &velocity;
}

void Avatar::SetVelocity(float2 _velocity)
{
	velocity = _velocity;
}

float Avatar::GetSpeed() const
{
	return SPEED;
}

Tilemap* Avatar::GetFloors() const
{
	return floors;
}

Tilemap* Avatar::GetLadders() const
{
	return ladders;
}
Rope* Avatar::GetRopes() const
{
	return ropes;
}
Zipline* Avatar::GetZiplines() const
{
	return ziplines;
}
size_t Avatar::GetZiplinesCount() const
{
	return ziplineCount;
}
size_t Avatar::GetRopeCount() const
{
	return ropeCount;
}

Camera* Avatar::GetCamera() const
{
	return cam;
}
Timer* Avatar::GetClimbTimer() const
{
	return climbTimer;
}

Box* Avatar::GetFloorCollider()
{
	return &floorCollider;
}

Box* Avatar::GetBoxCollider()
{
	return &boxCollider;
}

Input* Avatar::pGetInput()
{
	return &input;
}

float2 Avatar::getFloorPos()
{
	return FLOOR_POS;
}




