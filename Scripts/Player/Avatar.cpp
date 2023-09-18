#include "precomp.h"
#include "Avatar.h"

#include <iostream>

#include "Camera.h"


Avatar::Avatar() : sprite(nullptr), spriteFlipped(nullptr), tilemap(nullptr), cam(nullptr), velocity(), pos(), dir()
{
}

Avatar::~Avatar()
{
	delete sprite;
	delete spriteFlipped;
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

void Avatar::Init(const char* spritePath, Tilemap& _tilemap, Camera& _cam)
{
	tilemap = &_tilemap;
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


	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	//convert to screen position
	const float2 camPos = cam->GetPosition();
	const int x = static_cast<int>(pos.x - PLAYER_OFFSET.x - camPos.x); //center of the screen
	const int y = static_cast<int>(pos.y - PLAYER_OFFSET.y - camPos.y); //bottom of the sprite;

	if (dir.x) {
		flipX = dir.x < 0;
	}
	if (flipX > 0)
		spriteFlipped->Draw(screen, x, y);
	else
	{
		sprite->Draw(screen, x, y);

	}

#ifdef _DEBUG
	{
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

	}
#endif

}

void Avatar::GetInput(int2 input)
{
	dir = input;
}

void Avatar::SnapToFloor(float deltaTime, float2& floorPos)
{
	if (velocity.y < 0) {
		velocity.y = clamp(GRAVITY * deltaTime + velocity.y, -JUMP_FORCE, GRAVITY);
		return;
	}
	onFloor = tilemap->IsCollidingBox(pos + FLOOR_POS, floorCollider, floorPos);

	if (onFloor) {
		floorPos.y = floorPos.y - boxCollider.max.y / 2 - floorCollider.max.y / 2;
		pos.y = floorPos.y;
		velocity.y = 0;
		cout << "florr\n";
	}
	//add gravity
	else
	{
		cout << velocity;

		velocity.y = clamp(GRAVITY * deltaTime + velocity.y, -JUMP_FORCE, GRAVITY);
	}
}

void Avatar::Update(float deltaTime)
{

	//get input and velocity
	const float horizontal = (velocity.x + static_cast<float>(dir.x)) * SPEED;
	const float vertical = velocity.y * SPEED;



	const float newPosX = horizontal * deltaTime;
	const float newPosY = vertical * deltaTime;



	float2 newPos = pos + float2{ newPosX, 0 };
	float2 floorPos;

	if (!tilemap->IsCollidingBox(newPos, boxCollider))
		if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;
		}

	newPos = pos + float2{ 0,newPosY };

	if (!tilemap->IsCollidingBox(newPos, boxCollider))
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


	cam->UpdatePosition(deltaTime, newPos - CAMERA_OFFSET * flipX);

}


void Avatar::Jump()
{
	//check for floor
	onFloor = tilemap->IsCollidingBox(pos + FLOOR_POS, floorCollider);

	if (onFloor) {
		velocity.y = -JUMP_FORCE;
		jumping = true;
	}

}

float2 Avatar::GetPos() const
{
	return pos;
}

const float2* Avatar::GetPos()
{
	return &pos;
}

