#include "precomp.h"
#include "Avatar.h"

#include <iostream>

#include "Scripts/Utilities/MathLibrary.h"
#include "Scripts/Utilities/WorldLocalScreenTransf.h"


Avatar::Avatar() : sprite(nullptr), spriteFlipped(nullptr), tilemap(nullptr), velocity(), pos(), dir()
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

void Avatar::Init(const char* spritePath, Tilemap& _tilemap)
{
	tilemap = &_tilemap;
	char* spriteFlippedPath;
	GetFlippedPath(spritePath, spriteFlippedPath);

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	spriteFlipped = new Sprite(new Surface(spriteFlippedPath), NUMBER_FRAMES);
	pos.y = SCRHEIGHT / 2;
	pos.x = SCRWIDTH / 2;
	boxCollider = AABB(minCollider, maxCollider);

	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	const int x = static_cast<int>(pos.x) - sprite->GetWidth() * .5f; //center of the screen
	const int y = static_cast<int>(pos.y) - sprite->GetHeight() * .5f; //bottom of the sprite;
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

void Avatar::Move(int2 input)
{
	dir = input;
}
void Avatar::Update(float deltaTime)
{
	//from https://github.com/Tycro-Games/AUSS/blob/master/src/MoveablePlayer.cpp
	const float horizontal = dir.x;
	const float vertical = GRAVITY + velocity.y;//gravity


	const float newPosX = horizontal * deltaTime * speed;
	const float newPosY = vertical * deltaTime * speed;

	if (velocity.y < 0.01f)
		velocity.y += deltaTime * GRAVITY;


	if (!tilemap->IsCollidingBox(pos + newPosX, boxCollider))
		Movement(
			float2{ tilemap->transform.GetPosition().x - newPosX,0 },
			float2{ newPosX + pos.x,0 });

	if (!tilemap->IsCollidingBox(pos + newPosY, boxCollider))
		Movement(
			float2{ 0,tilemap->transform.GetPosition().y - newPosY },
			float2{ 0,pos.y + newPosY });


	dir = 0;
}
void Avatar::Movement(const float2 newTilemapPos, const float2 newPos)
{
	if (newTilemapPos.y == 0)
	{
		if (tilemap->FitsOnScreenX(newTilemapPos))
		{
			tilemap->transform.SetPos(newTilemapPos);
		}
		else {
			if (MathLibrary::OnScreen(newPos, boxCollider))
			{
				pos = newPos;
			}
		}
	}
	else
	{
		if (tilemap->FitsOnScreenY(newTilemapPos))
		{
			tilemap->transform.SetPos(newTilemapPos);
		}
		else
		{
			if (MathLibrary::OnScreen(newPos, boxCollider))
			{
				pos = newPos;
			}
		}

	}
}
void Avatar::Jump()
{
	//check for floor
	velocity.y = -12.0f;
}

