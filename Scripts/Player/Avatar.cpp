#include "precomp.h"
#include "Avatar.h"




Avatar::Avatar() : state(), sprite(nullptr), spriteFlipped(nullptr), floors(nullptr), ladders(nullptr), cam(nullptr),
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

void Avatar::Init(const char* spritePath, Tilemap& _floors, Tilemap& _ladders, Camera& _cam)
{
	floors = &_floors;
	ladders = &_ladders;

	cam = &_cam;
	char* spriteFlippedPath;
	GetFlippedPath(spritePath, spriteFlippedPath);

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	spriteFlipped = new Sprite(new Surface(spriteFlippedPath), NUMBER_FRAMES);
	//setting to world position
	pos.x = cam->GetPosition().x + SCRWIDTH / 2;
	pos.y = cam->GetPosition().y + SCRHEIGHT / 2;
	floorCollider = Box{ FLOOR_POS - FLOOR_SIZE,FLOOR_POS + FLOOR_SIZE };
	boxCollider = Box{ BOX_POS - BOX_SIZE,BOX_POS + BOX_SIZE };
	currentState = new MovingOnGroundState();
	currentState->OnEnter(*this);
	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	//convert to screen position
	const float2 camPos = cam->GetPosition();
	const int x = static_cast<int>(pos.x - PLAYER_OFFSET.x - camPos.x);
	const int y = static_cast<int>(pos.y - PLAYER_OFFSET.y - camPos.y);

	if (dir.x) {
		flipX = -dir.x;
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

void Avatar::SnapToFloor(float deltaTime, float2& floorPos)
{
	if (velocity.y < 0) {
		velocity.y = clamp(GRAVITY * deltaTime + velocity.y, velocity.y, GRAVITY);
		return;
	}
	canJump = floors->IsCollidingBox(pos, floorCollider, floorPos);

	if (canJump) {
		floorPos.y = floorPos.y - boxCollider.max.y / 2 - floorCollider.max.y / 2;
		pos.y = floorPos.y;
		velocity.y = 0;

	}
	//add gravity
	else
	{

		velocity.y = clamp(GRAVITY * deltaTime + velocity.y, velocity.y, GRAVITY);
	}

}

void Avatar::SetState(float2 floorPos)
{

	if (climbTimer->elapsed() >= climbDelay && state == FREEMOVE &&
		ladders->IsCollidingBox(pos, boxCollider, floorPos)) {
		climbTimer->reset();
		state = CLIMBPING;
		pos = floorPos + boxCollider.max.y / 2 + floorCollider.max.y / 2;
		velocity.y = 0;
	}
	else if (!ladders->IsCollidingBox(pos, boxCollider))
	{
		state = FREEMOVE;


	}
}

void Avatar::Update(float deltaTime)
{
	//get input and velocity
	float vertical;
	float horizontal;

	float2 floorPos = 0;
	float newPosY;
	float newPosX;
	float2 newPos = 0;
	/*State* newState = currentState->Update(*this, input, deltaTime);
	if (newState != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = newState;
		currentState->OnEnter(*this);
	}
	cam->UpdatePosition(deltaTime, pos, float2{ CAMERA_OFFSET.x * static_cast<float>(flipX),
		CAMERA_OFFSET.y });*/
	switch (state)
	{
	case FREEMOVE:
		horizontal = (velocity.x + static_cast<float>(input.arrowKeys.x)) * SPEED;
		vertical = velocity.y * SPEED;
		newPosX = horizontal * deltaTime;
		newPosY = vertical * deltaTime;

		newPos = pos + float2{ newPosX, 0 };

		if (!floors->IsCollidingBox(newPos, floorCollider) && !floors->IsCollidingBox(newPos, boxCollider)) {
			if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
			{
				pos = newPos;

			}
		}


		newPos = pos + float2{ 0, newPosY };

		if (!floors->IsCollidingBox(newPos, floorCollider))
		{
			if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
			{
				pos = newPos;

			}

		}
		else
		{
			velocity.y = 0;//hit something up so stop velocity
		}

		SnapToFloor(deltaTime, floorPos);

		break;
	case CLIMBPING:
		vertical = velocity.y + static_cast<float>(dir.y) * SPEED;
		velocity.y = 0;

		newPosY = vertical * deltaTime;


		newPos = pos + float2{ 0, newPosY };
		if (ladders->IsCollidingBox(newPos, boxCollider)) {
			if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
			{
				pos = newPos;
			}
		}
		else if (!floors->IsCollidingBox(newPos, boxCollider)) {
			if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
			{
				pos = newPos;
			}
		}


		break;
	default:
		break;
	}
	SetState(floorPos);
	cam->UpdatePosition(deltaTime, pos, float2{ CAMERA_OFFSET.x * static_cast<float>(flipX),
		CAMERA_OFFSET.y });
	



}


void Avatar::SetJumpInput(bool jumpInput)
{
	input.jumping = jumpInput;
	if (!jumpInput)
		return;
	  
	//check for floor
	if (state == CLIMBPING) {
		canJump = !floors->IsCollidingBox(pos, floorCollider) &&
			!floors->IsCollidingBox(pos, boxCollider);
		if (canJump) {
			velocity.y = -CLIMBING_JUMP_FORCE;
			state = FREEMOVE;
			climbTimer->reset();
		}
	}
	else {
		canJump = floors->IsCollidingBox(pos + FLOOR_POS, floorCollider);

		if (canJump) {
			velocity.y = -JUMP_FORCE;

		}
	}
}

float2 Avatar::GetPos() const
{
	return pos;
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


