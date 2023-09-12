#include "precomp.h"
#include "Avatar.h"

#include <iostream>

#include "Scripts/Utilities/MathLibrary.h"


Avatar::Avatar() : sprite(nullptr), spriteFlipped(nullptr), pos(), dir()
{
}

Avatar::~Avatar()
{
	delete sprite;
	delete spriteFlipped;
}

void Avatar::Init(const char* spritePath)
{
	//answer from https://stackoverflow.com/questions/10279718/append-char-to-string-in-c
	const size_t length = strlen(spritePath);
	char* spriteFlippedPath = new char[length + 2];//one more character and null character
	strcpy(spriteFlippedPath, spritePath);
	const char* c = strchr(spritePath, '.');

	spriteFlippedPath[length - strlen(c)] = 'f';
	strcpy(spriteFlippedPath + length - strlen(c) + 1, c);

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	spriteFlipped = new Sprite(new Surface(spriteFlippedPath), NUMBER_FRAMES);
	pos.y = SCRHEIGHT / 2;
	pos.x = SCRWIDTH / 2;
	aabb = AABB(minCollider, maxCollider);
	delete[] spriteFlippedPath;
}


void Avatar::Render(Surface* screen)
{
	int x = static_cast<int>(pos.x) - sprite->GetWidth() * .5f; //center of the screen
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
	//movement
	//only horizontal
	const float horizontal = dir.x;
	const float vertical = 9.8f;//gravity
	float2 newPosX = float2{ horizontal, 0 } *deltaTime * speed;
	float2 newPosY = float2{ 0, vertical } *deltaTime * speed;
	if (horizontal) {
		if (MathLibrary::OnScreen(pos + newPosX, aabb))
			pos += newPosX;
		cout << newPosX;
	}
	if (MathLibrary::OnScreen(pos + newPosY, aabb))
		pos += newPosY;

	dir = 0;
}

