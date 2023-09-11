// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"

#include <iostream>

#include "Scripts/Utilities/WorldLocalScreenTransf.h"

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	const float2 center = { SCRWIDTH / 2, SCRHEIGHT / 2 };
	WorldLocalScreenTransf::Init(center);

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png");

	tilemaps[BG].Init({ 0,0 }, "assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tilemaps[FLOOR].Init({ 0,0 }, "assets/160x160 background tilemap.png", "assets/Floors.tmx");
}

void Game::Render()
{
	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Render(screen);
	}
	//update input

	avatar.Render(screen);

}

void Game::Update(float deltaTime)
{
	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Update(deltaTime);
	}
	//tilemap is constrained so player moves

	avatar.Update(deltaTime);

}

void Tmpl8::Game::UpdateInput()
{
	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Move(int2(-horizontalMove, 0));
	}
	avatar.Move(int2(horizontalMove, verticalMove));

}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	//to seconds
	deltaTime /= 1000;
	screen->Clear(0);
	UpdateInput();
	Render();
	Update(deltaTime);
}

void Game::KeyUp(int key)
{
	switch (key)
	{
	case GLFW_KEY_LEFT:
		horizontalMove += 1;
		break;
	case GLFW_KEY_RIGHT:
		horizontalMove += -1;
		break;
	case GLFW_KEY_UP:
		verticalMove += 1;
		break;
	case GLFW_KEY_DOWN:
		verticalMove += -1;
		break;

	default:
		break;
	}
}

void Game::KeyDown(int key)
{
	switch (key)
	{
	case GLFW_KEY_LEFT:
		horizontalMove += -1;
		break;
	case GLFW_KEY_RIGHT:
		horizontalMove += 1;
		break;
	case GLFW_KEY_UP:
		verticalMove += -1;
		break;
	case GLFW_KEY_DOWN:
		verticalMove += 1;
		break;

	default:
		break;
	}
}

bool Game::TilemapMoves()
{
	for (int i = 0; i < COUNT; i++)
	{
		if (tilemaps->Moved())
			return true;

	}
	return false;
}
