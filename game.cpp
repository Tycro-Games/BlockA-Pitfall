// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"

#include <iostream>


Game::~Game()
{
	delete enviroment;
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{

	tilemaps[BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tilemaps[FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	//use {} for constructors calls - Erik
	enviroment = new Sprite{
		new Surface{
			tilemaps[FLOOR].GetWidth(),
		tilemaps[FLOOR].GetHeight()
		},1 };

	for (int i = 0; i < COUNT; i++) {
		tilemaps[i].Render(enviroment->GetSurface());
	}
	tilemaps[FLOOR].DebugBox(enviroment->GetSurface());


	cam.Init(float2{ 0, 700 }, enviroment);
	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tilemaps[FLOOR], cam);

}

void Game::Render()
{

	cam.Render(screen);
	avatar.Render(screen);

	//update input


}

void Game::Update(float deltaTime)
{
	//do something every frame
}


void Game::UpdateInput()
{
	if (isJumping)
	{
		avatar.Jump();
	}
	avatar.GetInput(int2(horizontalMove, verticalMove));

}

void Game::FixedUpdate(float deltaTime)
{

	avatar.Update(deltaTime);

}
// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	//to seconds
	static Timer fixedTimer;
	//static Timer a second;

	deltaTime *= 0.001f;


	screen->Clear(0);
	UpdateInput();
	if (fixedTimer.elapsed() >= 0.02f) {
		//cout << deltaTime << '\n';
		fixedTimer.reset();
		FixedUpdate(deltaTime);
	}
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


