#include "precomp.h"
#include "Avatar.h"

#include <iostream>

#include "Camera.h"
#include "Scripts/Utilities/MathLibrary.h"


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

	pos.x = cam->GetPosition().x + SCRWIDTH / 2;
	pos.y = cam->GetPosition().y + SCRHEIGHT / 2;
	boxCollider = AABB(minCollider, maxCollider);

	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	const float2 camPos = cam->GetPosition();
	int x = (static_cast<int>(pos.x) - boxCollider.max.x) - camPos.x; //center of the screen
	int y = (static_cast<int>(pos.y) - boxCollider.max.y) - camPos.y; //bottom of the sprite;
	if (dir.x) {
		flipX = dir.x < 0;
	}
	if (flipX)
		spriteFlipped->Draw(screen, x, y);
	else
	{
		sprite->Draw(screen, x, y);

	}

#ifdef _DEBUG
	{
		uint c = 255 << 16;
		int x = (static_cast<int>(pos.x)) - camPos.x; //center of the screen
		int y = (static_cast<int>(pos.y)) - camPos.y; //bottom of the sprite;

		screen->Box(x + boxCollider.min.x, y + boxCollider.min.y, x + boxCollider.max.x, y + boxCollider.max.y, c);
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
	//switch with circle
	onFloor = tilemap->IsCollidingBox(pos + float2{0, 5}, boxCollider, floorPos);

	if (onFloor) {
		floorPos.y = floorPos.y - boxCollider.max.y / 2;
		pos.y = floorPos.y;
	}


	const float horizontal = dir.x;
	if (!onFloor && velocity.y <= GRAVITY)
		velocity.y += deltaTime * FALL_SPEED;

	float vertical = velocity.y;



	const float newPosX = horizontal * deltaTime * HORIZONTAL_SPEED;
	const float newPosY = vertical * deltaTime * VERTICAL_SPEED;


	cout << velocity;

	float2 newPos = pos + float2{ newPosX, 0 };
	cam->UpdatePosition(deltaTime, newPos);
	if (!tilemap->IsCollidingBox(newPos, boxCollider))
		if (MathLibrary::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;
		}

	newPos = pos + float2{ 0, newPosY };
	cam->UpdatePosition(deltaTime, newPos);

	if (!tilemap->IsCollidingBox(newPos, boxCollider))
	{

		if (MathLibrary::OnScreen(newPos - cam->GetPosition(), boxCollider))
		{
			pos = newPos;
		}

	}
	else
	{
		velocity.y = 0;

	}




	dir = 0;
}


void Avatar::Jump()
{
	//check for floor
	if (onFloor) {
		velocity.y = -GRAVITY * 2.0f;
		jumping = true;
	}

}
//ask about this, how to make it const?
float2 Avatar::GetPos()
{
	return pos;
}

