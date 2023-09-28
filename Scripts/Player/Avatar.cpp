#include "precomp.h"
#include "Avatar.h"




Avatar::Avatar() : sprite(nullptr), spriteFlipped(nullptr), floors(nullptr), ladders(nullptr), ziplines(nullptr),
ropes(nullptr),
cam(nullptr),
currentState(nullptr),
velocity(),
pos()
{
	climbTimer = new Timer();
	jumpTimer = new Timer();
}

Avatar::~Avatar()
{
	delete climbTimer;
	delete jumpTimer;
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
	jumpCollider = Box{ JUMP_POS - float2{JUMP_SIZE_X,JUMP_SIZE_Y},JUMP_POS + float2{JUMP_SIZE_X,JUMP_SIZE_Y} };
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
	int directionToLook = 1;
	if (velocity.x > 0.1f)
		directionToLook = 1;
	else if ((velocity.x) < -0.1f)
	{
		directionToLook = -1;
	}
	else
		directionToLook = 0;
	if (directionToLook) {
		flipX = -directionToLook;
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
	Box fl = AABB::At({ debugX, debugY }, jumpCollider);
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

void Avatar::Update(float deltaTime)
{
	UpdateCurrentState(deltaTime);
	input.jumping = false;
	input.smallJump = false;

	cam->UpdatePosition(deltaTime, GetBoxColliderPos(), static_cast<float>(flipX));
}
bool Avatar::IsCollidingLadders( const Box& col, float2& floorPos) const
{
	return ladders->IsCollidingBox(pos, col, floorPos);
}
bool Avatar::IsCollidingLadders(const float2& newPos, const Box& col) const
{
	return ladders->IsCollidingBox(newPos, col);
}
bool Avatar::IsCollidingLadders( const Box& col) const
{
	return ladders->IsCollidingBox(pos, col);
}
bool Avatar::IsCollidingFloors(const float2& newPos, const Box& col) const
{
	return floors->IsCollidingBox(newPos, col);
}
bool Avatar::IsCollidingFloors( const Box& col) const
{
	return floors->IsCollidingBox(pos, col);
}
bool Avatar::IsCollidingFloors(const Box& col, float2& floorPos) const
{
	return floors->IsCollidingBox(pos, col, floorPos);
}

bool Avatar::IsCollidingRopes(float2*& pMovingPart) const
{
	for (uint i = 0; i < ropeCount; i++) {
		if (ropes[i].GetOnScreen()) {


			float2 toPlayer = (pos + BOX_POS) - ropes[i].GetMovingPart();
			if (length(toPlayer) <= RADIUS_TO_ROPE) {

				pMovingPart = ropes[i].pGetMovingPart();
				return true;
			}
		}
	}
	return false;
}
bool Avatar::IsCollidingZiplines(float2& _normal,
	float2& _start,
	float2& _end) const
{
	for (uint i = 0; i < ziplineCount; i++)
		if (ziplines[i].GetOnScreen()) {
			float2 start = 0;
			float2 end = 0;
			ziplines[i].GetStartEnd(start, end);

			float2 a = end - start;
			float2 toPlayer = -(start - (pos + BOX_POS));
			float2 toPlayerP = normalize(a) * clamp(length(toPlayer), 0.0f, length(a) - ZIPLINE_OFFSET_END);//not after the end
			float2 normal = toPlayer - toPlayerP;
			if (length(normal) <= RADIUS_TO_ZIPLINE) {
				_normal = normal;
				_start = start;
				_end = end;
				return true;
			}
		}
	return false;

}
bool Avatar::IsClimbTimerFinished(float time) const
{
	return climbTimer->elapsed() >= time;
}
void Avatar::SetJumpInput(bool jumpInput)
{
	if (jumpInput) {
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
		if (startedJump) {
			if (jumpTimer->elapsed() <= SMALL_JUMP_END) {
				input.smallJump = true;
			}

		}
		startedJump = false;
		alreadyJumped = false;
		jumpTimer->reset();

	}
	//input.jumping = jumpInput;
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

const Box& Avatar::GetFloorCollider() const
{
	return floorCollider;
}

const Box& Avatar::GetBoxCollider() const
{
	return boxCollider;
}
const Box& Avatar::GetJumpCollider() const
{
	return jumpCollider;
}

const Input& Avatar::GetInput() const
{
	return input;
}

float2 Avatar::GetFloorPos() const
{
	return FLOOR_POS;
}
float2 Avatar::GetJumpPos() const
{
	return JUMP_POS;
}




