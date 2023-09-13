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
	pos.x = cam->GetPosition().x + SCRHEIGHT / 2;
	pos.y = cam->GetPosition().y + SCRWIDTH / 2;
	boxCollider = AABB(minCollider, maxCollider);

	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	const float2 camPos = cam->GetPosition();
	const int x =  static_cast<int>(pos.x) - sprite->GetWidth() / 2- camPos.x; //center of the screen
	const int y =  static_cast<int>(pos.y) - sprite->GetHeight() / 2- camPos.y; //bottom of the sprite;
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
	const int2 size = 15;
	uint c = 255 << 16;
	screen->Box(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, c);

#endif

}

void Avatar::GetInput(int2 input)
{
	dir = input;
}
void Avatar::Update(float deltaTime)
{
	const float horizontal = dir.x;
	const float vertical = GRAVITY + velocity.y;//gravity


	const float newPosX = horizontal * deltaTime * speed;
	const float newPosY = vertical * deltaTime * speed;
	if (velocity.y < 0.01f)
		velocity.y += deltaTime * GRAVITY;

	float2 newPos = pos + float2{ newPosX, 0 };
	if (!tilemap->IsCollidingBox(cam->GetPosition() + newPos, boxCollider))
		if (!cam->UpdatePosition(deltaTime, newPos)) //did not move
		{
			if (MathLibrary::OnScreen(newPos, boxCollider))
			{
				pos = newPos;
			}
		}

	newPos = pos + float2{ 0, newPosY };
	if (!tilemap->IsCollidingBox(cam->GetPosition() + newPos, boxCollider))

		if (!cam->UpdatePosition(deltaTime, newPos)) //did not move
		{
			if (MathLibrary::OnScreen(newPos, boxCollider))
			{
				pos = newPos;
			}
		}


	dir = 0;
}


void Avatar::Jump()
{
	//check for floor
	velocity.y = -12.0f;
}
//ask about this, how to make it const?
float2 Avatar::GetPos()
{
	return pos;
}

