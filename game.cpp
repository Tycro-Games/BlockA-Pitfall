// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"



Game::~Game()
{
	delete enviroment;
	delete parallaxSprite;
	delete[] ropes;
	delete[] ziplines;
	delete[] spikes;
}

void Game::AddObservers()
{
	for (uint i = 0; i < countSpikes; i++)
		spikes[i].GetSubject()->AddObserver(healthBar);
	avatar.GetSubject()->AddObserver(cam);
}

void Game::SetUpCamera()
{
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
}

void Game::AddAllEntities()
{
	for (uint i = 0; i < countZiplines / 2; i++)
	{
		AddPreEntity(ziplines[i]);


	}
	for (uint i = 0; i < countRopes; i++)
	{
		AddPreEntity(ropes[i]);


	}
	for (uint i = 0; i < countSpikes; i++)
	{
		AddPreEntity(spikes[i]);

	}

	AddAfterEntity(avatar);
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
#pragma region 
	tileMaps[Tilemap::PARALLAX].Init("assets/Pitfall_tilesheet.png", "assets/Parallax.tmx");
	tileMaps[Tilemap::BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tileMaps[Tilemap::FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tileMaps[Tilemap::LADDERS].Init("assets/Pitfall_tilesheet.png", "assets/Ladders.tmx");
	//non tiles
	//learned how to do pragma regions  from John Gear

	nonTiles[SpawnNonTiles::ROPE].Init("assets/Ropes.tmx");
	nonTiles[SpawnNonTiles::ZIPLINE].Init("assets/Ziplines.tmx");
	nonTiles[SpawnNonTiles::SPIKES].Init("assets/Spikes.tmx");

	countRopes = nonTiles[SpawnNonTiles::ROPE].GetCount();
	countZiplines = nonTiles[SpawnNonTiles::ZIPLINE].GetCount();

	countSpikes = nonTiles[SpawnNonTiles::SPIKES].GetCount();

	ropes = new Rope[countRopes];

	ziplines = new Zipline[countZiplines];

	spikes = new Spike[countSpikes];


	for (uint i = 0; i < countRopes; i++)
	{

		ropes[i].Init(nonTiles[SpawnNonTiles::ROPE].GetPosition(i));

	}
	uint zIndex = 0;
	for (uint i = 0; i < countZiplines; i += 2)
	{
		ziplines[zIndex++].Init(nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i),
			nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i + 1));


	}
	for (uint i = 0; i < countSpikes; i++)
	{
		spikes[i].Init(nonTiles[SpawnNonTiles::SPIKES].GetPosition(i), &avatar);
	}
#pragma endregion MAP_SET_UP
	healthBar.Init("assets/heart_animated_1.png");

	SetUpCamera();

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tileMaps[Tilemap::FLOOR], tileMaps[Tilemap::LADDERS], ropes, countRopes, ziplines, countZiplines, cam);


	AddAllEntities();
	AddObservers();
}

void Game::RenderUI()
{
	healthBar.Render(screen);
}

void Game::Render()
{
	//clean the surfaces
	screen->Clear(0);
	cam.CleanPreRenderSurface();

	//first to call
	cam.RenderTilemaps();

	for (uint i = 0; i < indexPreEntities; i++)
	{
		preCamera[i]->Render(cam.pGetPreRender());
	}
	for (uint i = 0; i < indexAfterEntities; i++)
	{
		afterCamera[i]->Render(cam.pGetPreRender());
	}
	cam.Render(screen);

	RenderUI();


}

void Game::Update(float deltaTime)
{

	spikes[0].Update(deltaTime);

}


void Game::UpdateInput()
{
	avatar.SetInput(input.arrowKeys);

	avatar.SetJumpInput(input.jumping);
}



void Game::FixedUpdate(float deltaTime)
{
	for (uint i = 0; i < indexPreEntities; i++)
	{
		preCamera[i]->Update(deltaTime);
	}
	//camera position also gets updated
	cam.Update(deltaTime);

	for (uint i = 0; i < indexAfterEntities; i++)
	{
		afterCamera[i]->Update(deltaTime);
	}

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

void Game::RemoveObservers()
{
	spikes->GetSubject()->RemoveObserver(healthBar);
	avatar.GetSubject()->RemoveObserver(cam);
}

void Game::Shutdown()
{
	//remove observers
	RemoveObservers();
}

//this is called automatically now
//void Game::MouseWheel(float wheelDirection)
//{
//	cam.SetInputScaling(wheelDirection);
//}

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

void Game::AddPreEntity(Entity& entity)
{
	preCamera[indexPreEntities++] = &entity;
}
void Game::AddAfterEntity(Entity& entity)
{
	afterCamera[indexAfterEntities++] = &entity;
}


