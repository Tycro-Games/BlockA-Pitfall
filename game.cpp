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
	delete[] ropes;
	delete[] ziplines;
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	tilemaps[Tilemap::PARALLAX].Init("assets/Pitfall_tilesheet.png", "assets/Parallax.tmx");
	tilemaps[Tilemap::BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tilemaps[Tilemap::FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tilemaps[Tilemap::LADDERS].Init("assets/Pitfall_tilesheet.png", "assets/Ladders.tmx");
	//non tiles
	//learned how to do this from John Gear
#pragma region 
	ropesPos.Init("assets/Ropes.tmx");
	ziplinesPos.Init("assets/Ziplines.tmx");
	size_t countRopes = ropesPos.GetCount();
	size_t countZiplines = ropesPos.GetCount();
	ropes = new Rope[countRopes];
	ziplines = new Zipline[countZiplines];
	for (uint i = 0; i < countRopes; i++)
	{
		ropes[i].Init(ropesPos.GetPosition(i));
	}
	for (uint i = 0; i < countZiplines; i += 2)
	{
		ziplines[i].Init(ziplinesPos.GetPosition(i), ziplinesPos.GetPosition(i + 1) );
	}
#pragma endregion NON_TILE

	//it gets owned by the sprite so we don't have to delete it
	Surface* surf = new Surface(tilemaps[Tilemap::FLOOR].GetWidth(), tilemaps[Tilemap::FLOOR].GetHeight());

	Surface* par = new Surface(tilemaps[Tilemap::PARALLAX].GetWidth(), tilemaps[Tilemap::PARALLAX].GetHeight());
	par->Clear(0x000001);
	surf->Clear(0xff000000);
	enviroment = new Sprite(surf, 1);
	parallaxSprite = new Sprite(par, 1);
	for (int i = Tilemap::BG; i < Tilemap::COUNT; i++) {
		tilemaps[i].Render(enviroment->GetSurface());
	}
	tilemaps[Tilemap::PARALLAX].Render(parallaxSprite->GetSurface());

#ifdef _DEBUG
	tilemaps[Tilemap::FLOOR].DebugBox(enviroment->GetSurface());
#endif

	cam.Init(float2{ 0.0f, 700.0f }, enviroment, parallaxSprite);

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tilemaps[Tilemap::FLOOR], tilemaps[Tilemap::LADDERS], cam);
	r.Init({ 500,700 });
	z.Init({ 500,1200 }, { 200,1300 });

}

void Game::Render()
{
	screen->Clear(0);
	cam.CleanPreRenderSurface();

	//first to call
	cam.RenderTilemaps();

	for (uint i = 0; i < ropesPos.GetCount(); i++)
		ropes[i].Render(cam.pGetPreRender());
	for (uint i = 0; i < ziplinesPos.GetCount(); i++)
		ziplines[i].Render(cam.pGetPreRender());

	avatar.Render(cam.pGetPreRender());

	cam.RenderToScreen(screen);


}

void Game::Update(float deltaTime)
{
	//do something every frame
	for (uint i = 0; i < ropesPos.GetCount(); i++)
		ropes[i].Update(deltaTime);
	cam.Update(deltaTime);
}


void Game::UpdateInput()
{
	avatar.SetInput(int2(horizontalMove, verticalMove));

	if (isJumping)
		avatar.SetJumpInput(isJumping);
	isJumping = false;
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

void Game::MouseWheel(float wheelDirection)
{
	cam.GetInput(wheelDirection);
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


