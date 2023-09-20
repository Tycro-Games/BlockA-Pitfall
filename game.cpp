// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"

#include <iostream>


Game::~Game()
{
	delete enviroment;
	delete parallaxSprite;
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	tilemaps[PARALLAX].Init("assets/Pitfall_tilesheet.png", "assets/Parallax.tmx");
	tilemaps[BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tilemaps[FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tilemaps[LADDERS].Init("assets/Pitfall_tilesheet.png", "assets/Ropes.tmx");
	//it gets owned by the sprite so we don't have to delete it
	Surface* surf = new Surface(tilemaps[FLOOR].GetWidth(), tilemaps[FLOOR].GetHeight());

	Surface* par = new Surface(tilemaps[PARALLAX].GetWidth(), tilemaps[PARALLAX].GetHeight());
	par->Clear(0x000001);
	surf->Clear(0xFF000000);
	enviroment = new Sprite(surf, 1);
	parallaxSprite = new Sprite(par, 1);
	for (int i = BG; i < COUNT; i++) {
		tilemaps[i].Render(enviroment->GetSurface());
	}
	tilemaps[PARALLAX].Render(parallaxSprite->GetSurface());
	
#ifdef _DEBUG
	tilemaps[FLOOR].DebugBox(enviroment->GetSurface());
#endif

	cam.Init(float2{ 0.0f, 700.0f }, enviroment, parallaxSprite);

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tilemaps[FLOOR], tilemaps[LADDERS], cam);

}

void Game::Render()
{
	screen->Clear(0);

	cam.Render(screen);

	avatar.Render(screen);



}

void Game::Update(float deltaTime)
{
	//do something every frame
}


void Game::UpdateInput()
{
	avatar.GetInput(int2(horizontalMove, verticalMove));

	if (isJumping)
	{
		avatar.Jump();
		isJumping = false;
	}

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


	UpdateInput();
	if (fixedTimer.elapsed() >= fixedDeltaTime) {
		//cout << deltaTime << '\n';
		fixedTimer.reset();
		FixedUpdate(fixedDeltaTime);
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


