#include "precomp.h"
#include "Avatar.h"

#include <iostream>

Avatar::Avatar()
= default;

Avatar::~Avatar()
{
	delete sprite;
}

void Avatar::Init(const char* spritePath)
{

	sprite = new Sprite(new Surface(spritePath), NUMBER_FRAMES);
	pos.y = SCRHEIGHT / 2;
	pos.x = SCRWIDTH / 2;
}


void Avatar::Render(Surface* screen)
{
	int x = static_cast<int>(pos.x) - sprite->GetWidth() *.5f; //center of the screen
	const int y = static_cast<int>(pos.y) - sprite->GetHeight(); //bottom of the sprite;
	if (dir.x)
		flipX = dir.x < 0;
	sprite->Draw(screen, x, y, flipX);

#ifdef _DEBUG
	screen->Box(pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10, 255);

#endif

}

void Avatar::Move(int2 input)
{
	dir = input;
}
void Avatar::Update(float deltaTime)
{
	//movement
	pos += static_cast<float2>(dir) * deltaTime * speed;
	dir = 0;
}

