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
	const int width = sprite->GetWidth() * 3;
	const int height = sprite->GetHeight() * 3;
	sprite->DrawScaled(pos.x - width / 2, pos.y - height *0.75f,
		width, height, screen);
}

void Avatar::Move(int2 input)
{
	dir = input;
}
void Avatar::Update(float deltaTime)
{
	//movement
	pos += dir * deltaTime * speed;
	dir = 0;
}

