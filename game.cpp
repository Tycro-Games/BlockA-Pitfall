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


	tilemaps[BG].Init({ 0,0 }, "assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tilemaps[FLOOR].Init({ 0,0 }, "assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tilemaps[BG].transform.SetParent(tilemaps[FLOOR].transform);
	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tilemaps[FLOOR]);

}

void Game::Render()
{
	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Render(screen);
	}
	tilemaps[FLOOR].DebugBox(screen);
	//update input

	avatar.Render(screen);

}

void Game::Update(float deltaTime)
{
	if (isJumping)
	{
		avatar.Jump();
	}

}

void Game::UpdateInput()
{
	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Move(int2(-horizontalMove, -verticalMove));
	}
	avatar.Move(int2(horizontalMove, verticalMove));

}

void Game::FixedUpdate(float delta_time)
{
	avatar.Update(delta_time);

	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Update(delta_time);
	}
	//to do tilemap is constrained so player moves

}
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	//to seconds
	static Timer fixedTimer;
	//static Timer asecond;

	deltaTime *= 0.001f;


	screen->Clear(0);

	UpdateInput();
	if (fixedTimer.elapsed() > 0.02f) {
		//cout << deltaTime << '\n';
		fixedTimer.reset();
		FixedUpdate(deltaTime);
	}
	Render();
	/*if (asecond.elapsed() > 1.0f) {
		cout << "one second passed\n";
		asecond.reset();
	}*/


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
	case GLFW_KEY_SPACE:
		isJumping = false;
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
	case GLFW_KEY_SPACE:
		isJumping = true;
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
