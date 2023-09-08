// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	avatar.Init("assets/PlayerSheet/_Idle.png");
	background.Init(float2{ SCRWIDTH / 2,SCRHEIGHT / 2 }, "assets/PitfallTilesheet.png", "assets/tilemap.tmx");
}

void Game::Render()
{
	background.Render(screen);
	avatar.Render(screen);
}

void Game::Update(float deltaTime)
{
	background.Move(int2(-horizontalMove, -verticalMove));
	background.Update(deltaTime);
	avatar.Move(int2(horizontalMove, verticalMove));
	//avatar.Update(deltaTime);

}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	//to seconds
	deltaTime /= 1000;
	screen->Clear(0);
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
