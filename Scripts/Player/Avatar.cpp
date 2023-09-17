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
	boxCollider = AABB(minCollider, maxCollider);

	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	//convert to screen position
	const float2 camPos = cam->GetPosition();
	const int x = static_cast<int>(pos.x - boxCollider.max.x - camPos.x); //center of the screen
	const int y = static_cast<int>(pos.y - boxCollider.max.y - camPos.y); //bottom of the sprite;

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
		const uint c = 255 << 16;
		//on screen positions
		const float debugX = pos.x - camPos.x;
		const float debugY = pos.y - camPos.y;

		AABB a = boxCollider.At({ debugX, debugY });
		screen->Box(
			static_cast<int>(a.min.x),
			static_cast<int>(a.min.y),
			static_cast<int>(a.max.x),
			static_cast<int>(a.max.y),
			c);
	}
#endif

}

void Avatar::GetInput(int2 input)
{
	dir = input;
}
void Avatar::Update(float deltaTime)
{
	float2 floorPos;
	//TODO switch with circle
	onFloor = tilemap->IsCollidingBox(pos + float2{0, 5}, boxCollider, floorPos);

	if (onFloor) {
		floorPos.y = floorPos.y - boxCollider.max.y / 2;
		pos.y = floorPos.y;
	}
	//add gravity
	else
	{
		velocity.y = clamp(GRAVITY * deltaTime + velocity.y, -JUMP_FORCE, GRAVITY);
	}
	//get input and velocity
	const float horizontal = velocity.x + static_cast<float>(dir.x);
	const float vertical = velocity.y;



	const float newPosX = horizontal * deltaTime * SPEED;
	const float newPosY = vertical * deltaTime * SPEED;


	cout << velocity;

	float2 newPos = pos + float2{ newPosX, 0 };

	if (!tilemap->IsCollidingBox(newPos, boxCollider))
		if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;
		}

	newPos = pos + float2{ 0, newPosY };

	if (!tilemap->IsCollidingBox(newPos, boxCollider))
	{

		if (Camera::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;
		}

	}
	else
	{
		//TODO make velocity really stop when on the ground
		velocity.y = 0;
	}



	cam->UpdatePosition(deltaTime, newPos - CAMERA_OFFSET * flipX);

}


void Avatar::Jump()
{
	//check for floor
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

