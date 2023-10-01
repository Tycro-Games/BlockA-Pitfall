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
	tileMaps[Tilemap::PARALLAX].Init("assets/Pitfall_tilesheet.png", "assets/Parallax.tmx");
	tileMaps[Tilemap::BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tileMaps[Tilemap::FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tileMaps[Tilemap::LADDERS].Init("assets/Pitfall_tilesheet.png", "assets/Ladders.tmx");
	//non tiles
	//learned how to do this from John Gear
#pragma region 
	nonTiles[SpawnNonTiles::ROPE].Init("assets/Ropes.tmx");
	nonTiles[SpawnNonTiles::ZIPLINE].Init("assets/Ziplines.tmx");
	countRopes = nonTiles[SpawnNonTiles::ROPE].GetCount();
	countZiplines = nonTiles[SpawnNonTiles::ZIPLINE].GetCount();
	ropes = new Rope[countRopes];

	ziplines = new Zipline[countZiplines];
	for (uint i = 0; i < countRopes; i++)
	{
		ropes[i].Init(nonTiles[SpawnNonTiles::ROPE].GetPosition(i));
	}
	for (uint i = 0; i < countZiplines; i += 2)
	{
		ziplines[i].Init(nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i),
			nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i + 1));
	}
#pragma endregion NON_TILE

	//it gets owned by the sprite so we don't have to delete it
	Surface* surf = new Surface(tileMaps[Tilemap::FLOOR].GetWidth(), tileMaps[Tilemap::FLOOR].GetHeight());

	Surface* par = new Surface(tileMaps[Tilemap::PARALLAX].GetWidth(), tileMaps[Tilemap::PARALLAX].GetHeight());
	par->Clear(0x000001);
	surf->Clear(0xff000000);
	enviroment = new Sprite(surf, 1);
	parallaxSprite = new Sprite(par, 1);
	for (int i = Tilemap::BG; i < Tilemap::COUNT; i++) {
		tileMaps[i].Render(enviroment->GetSurface());
	}
	tileMaps[Tilemap::PARALLAX].Render(parallaxSprite->GetSurface());

#ifdef _DEBUG
	tileMaps[Tilemap::FLOOR].DebugBox(enviroment->GetSurface());
#endif

	cam.Init(float2{ 200, 400.0f }, enviroment, parallaxSprite);

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tileMaps[Tilemap::FLOOR], tileMaps[Tilemap::LADDERS], ropes, countRopes, ziplines, countZiplines, cam);


}

void Game::Render()
{
	screen->Clear(0);
	cam.CleanPreRenderSurface();

	//first to call
	cam.RenderTilemaps();
	/*float2 offset = { 50,100 };//bezier test
	float2 a = { SCRWIDTH / 2, SCRHEIGHT / 2 };
	float2 b = { SCRWIDTH / 2, SCRHEIGHT / 2 + offset.y };
	float2 c = { SCRWIDTH / 2 + offset.x, SCRHEIGHT / 2 + offset.y + offset.x };
	float2 d = { SCRWIDTH / 2 + offset.x*2, SCRHEIGHT / 2 + offset.y*2 + offset.x };
	screen->BezierCurve(255, a, b, c, d, 1);

	screen->Plot(a.x,a.y,0xFFFFFF);
	screen->Plot(b.x,b.y,0xFFFFFF);
	screen->Plot(c.x,c.y,0xFFFFFF);
	screen->Plot(d.x,d.y,0xFFFFFF);*/


	for (uint i = 0; i < countRopes; i++)
		ropes[i].Render(cam.pGetPreRender());
	for (uint i = 0; i < countZiplines; i++)
		ziplines[i].Render(cam.pGetPreRender());

	avatar.Render(cam.pGetPreRender());

	cam.RenderToScreen(screen);


}

void Game::Update(float deltaTime)
{



}


void Game::UpdateInput()
{
	avatar.SetInput(input.arrowKeys);

	avatar.SetJumpInput(input.jumping);
}



void Game::FixedUpdate(float deltaTime)
{
	for (uint i = 0; i < countRopes; i++) {
		ropes[i].Update(deltaTime);

	}
	for (uint i = 0; i < countZiplines; i++) {
		ziplines[i].Update(deltaTime);

	}
	//camera positon also gets updated
	cam.Update(deltaTime);

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

	if (fixedTimer.elapsed() > fixedDeltaTime) {
		fixedTimer.reset();
		FixedUpdate(fixedDeltaTime);
	}

	Update(deltaTime);

	Render();


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
		input.arrowKeys.x += 1;
		break;
	case GLFW_KEY_RIGHT:
		input.arrowKeys.x += -1;
		break;
	case GLFW_KEY_UP:
		input.arrowKeys.y += 1;
		break;
	case GLFW_KEY_DOWN:
		input.arrowKeys.y += -1;
		break;
	case GLFW_KEY_SPACE:
		input.jumping = false;
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
		input.arrowKeys.x += -1;
		break;
	case GLFW_KEY_RIGHT:
		input.arrowKeys.x += 1;
		break;
	case GLFW_KEY_UP:
		input.arrowKeys.y += -1;
		break;
	case GLFW_KEY_DOWN:
		input.arrowKeys.y += 1;
		break;
	case GLFW_KEY_SPACE:
		input.jumping = true;
		break;
	default:
		break;
	}
}


