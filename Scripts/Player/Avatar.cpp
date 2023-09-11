#include "precomp.h"
#include "Avatar.h"

#include <iostream>

#include "Scripts/Utilities/MathLibrary.h"


Avatar::Avatar() : sprite(nullptr), pos(), dir()
{
}

Avatar::~Avatar()
{
	delete sprite;
}

void Avatar::Init(const char* spritePath)
{

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	pos.y = SCRHEIGHT / 2;
	pos.x = SCRWIDTH / 2;
	aabb = AABB(minCollider, maxCollider);
}


void Avatar::Render(Surface* screen)
{
	int x = static_cast<int>(pos.x) - sprite->GetWidth() * .5f; //center of the screen
	const int y = static_cast<int>(pos.y) - sprite->GetHeight() * .5f; //bottom of the sprite;
	if (dir.x)
		flipX = dir.x < 0;
	sprite->Draw(screen, x, y, flipX);

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

