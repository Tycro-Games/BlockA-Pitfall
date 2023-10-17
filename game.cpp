// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"



Game::~Game()
{
	delete enviroment;
	delete parallaxSprite;
}

void Game::AddObservers()
{

	for (uint i = 0; i < spikes.GetCount(); i++)
		spikes[i].GetSubject()->AddObserver(healthBar);
	for (uint i = 0; i < boars.GetCount(); i++)
		boars[i].GetSubject()->AddObserver(healthBar);
	for (uint i = 0; i < monkeys.GetCount(); i++)
		monkeys[i].GetSubject()->AddObserver(healthBar);
	avatar.GetSubject()->AddObserver(cam);
	healthBar.GetSubject()->AddObserver(avatar);
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

	cam.Init(STARTING_POSITION, enviroment, parallaxSprite);
}

void Game::AddAllEntities()
{
	for (uint i = 0; i < ziplines.GetCount(); i++)
	{
		AddPreEntity(&ziplines[i]);


	}
	for (uint i = 0; i < ropes.GetCount(); i++)
	{
		AddPreEntity(&ropes[i]);


	}
	for (uint i = 0; i < elasticPlants.GetCount(); i++)
	{
		AddPreEntity(&elasticPlants[i]);


	}
	for (uint i = 0; i < spikes.GetCount(); i++)
	{
		AddPreEntity(&spikes[i]);

	}
	for (uint i = 0; i < boars.GetCount(); i++)
	{
		AddPreEntity(&boars[i]);

	}
	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		AddPreEntity(&monkeys[i]);

	}

	AddAfterEntity(&avatar);
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
	bool hasPairOfTwoPositions = true;
	nonTiles[SpawnNonTiles::ROPE].Init("assets/Ropes.tmx");
	nonTiles[SpawnNonTiles::ZIPLINE].Init("assets/Ziplines.tmx", hasPairOfTwoPositions);
	nonTiles[SpawnNonTiles::ELASTIC_PLANTS].Init("assets/ElasticPlants.tmx");
	nonTiles[SpawnNonTiles::SPIKES].Init("assets/Spikes.tmx");
	nonTiles[SpawnNonTiles::MONKEYS].Init("assets/Monkeys.tmx");
	nonTiles[SpawnNonTiles::BOARS].Init("assets/Boars.tmx", hasPairOfTwoPositions);
	//used https://www.3dgep.com/cpp-fast-track-9-colours/
	uint8_t countEnemies = 0;
	uint8_t countStatics = 0;
	size_t countZipRopes = nonTiles[SpawnNonTiles::ROPE].GetCount() << GetBitSpace(countStatics);
	countZipRopes = countZipRopes | nonTiles[SpawnNonTiles::ZIPLINE].GetCount() << GetBitSpace(countStatics);
	countZipRopes = countZipRopes | nonTiles[SpawnNonTiles::ELASTIC_PLANTS].GetCount() << GetBitSpace(countStatics);

	size_t countsEnemies = nonTiles[SpawnNonTiles::SPIKES].GetCount() << GetBitSpace(countEnemies);
	countsEnemies = countsEnemies | nonTiles[SpawnNonTiles::BOARS].GetCount() << GetBitSpace(countEnemies);
	countsEnemies = countsEnemies | nonTiles[SpawnNonTiles::MONKEYS].GetCount() << GetBitSpace(countEnemies);

	countEnemies = 1;
	countStatics = 1;

	size_t count = countZipRopes & 0b11111111;//255 in binary
	ropes.Init(count);


	uint8_t shift = GetBitSpace(countStatics);
	count = (countZipRopes & 0b11111111 << shift) >> shift;
	ziplines.Init(count);

	shift = GetBitSpace(countStatics);
	count = (countZipRopes & 0b11111111 << shift) >> shift;
	elasticPlants.Init(count);

	count = countsEnemies & 0b11111111;
	spikes.Init(count);

	shift = GetBitSpace(countEnemies);
	count = (countsEnemies & 0b11111111 << shift) >> shift;

	boars.Init(count);

	shift = GetBitSpace(countEnemies);
	count = (countsEnemies & 0b11111111 << shift) >> shift;
	monkeys.Init(count);

	for (uint i = 0; i < ropes.GetCount(); i++)
	{

		ropes[i].Init(nonTiles[SpawnNonTiles::ROPE].GetPosition(i));

	}
	uint zIndex = 0;
	for (uint i = 0; i < ziplines.GetCount() * 2; i += 2)
	{
		ziplines[zIndex++].Init(nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i),
			nonTiles[SpawnNonTiles::ZIPLINE].GetPosition(i + 1));


	}
	for (uint i = 0; i < elasticPlants.GetCount(); i++)
	{
		elasticPlants[i].Init(nonTiles[SpawnNonTiles::ELASTIC_PLANTS].GetPosition(i));


	}
	for (uint i = 0; i < spikes.GetCount(); i++)
	{
		spikes[i].Init(nonTiles[SpawnNonTiles::SPIKES].GetPosition(i), avatar);
	}
	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		monkeys[i].Init(nonTiles[SpawnNonTiles::MONKEYS].GetPosition(i), &tileMaps[Tilemap::FLOOR], &tileMaps[Tilemap::LADDERS], avatar);
	}
	zIndex = 0;

	for (uint i = 0; i < boars.GetCount() * 2; i += 2)
	{
		boars[zIndex++].Init(nonTiles[SpawnNonTiles::BOARS].GetPosition(i),
			nonTiles[SpawnNonTiles::BOARS].GetPosition(i + 1)
			, avatar);
	}
#pragma endregion MAP_SET_UP
	healthBar.Init("assets/heart_animated_1.png");
	
	SetUpCamera();

	avatar.Init("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png", tileMaps[Tilemap::FLOOR], tileMaps[Tilemap::LADDERS], ropes, ziplines, elasticPlants, cam);


	AddAllEntities();
	AddObservers();
}

void Game::RenderUI()
{
	healthBar.Render(screen);
	//screen->Print("HEa23sdz;/", 100, 100, YELLOW);
	score.Render(screen);
	coinScore.Render(screen);

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
		if (preCameraUpdate[i]->GetActive())
			preCameraUpdate[i]->Render(cam.pGetPreRender());
	}
	for (uint i = 0; i < indexAfterEntities; i++)
	{
		if (afterCameraUpdate[i]->GetActive())
			afterCameraUpdate[i]->Render(cam.pGetPreRender());
	}
	//screen->Print();

	cam.Render(screen);

	RenderUI();


}




void Game::UpdateInput()
{
	avatar.SetInput(input.arrowKeys);

	avatar.SetJumpInput(input.jumping);
	avatar.SetShootInput(input.shooting);
}



void Game::FixedUpdate(float deltaTime)
{
	for (uint i = 0; i < indexPreEntities; i++)
	{
		if (preCameraUpdate[i]->GetActive())

			preCameraUpdate[i]->Update(deltaTime);
	}
	//camera position also gets updated
	cam.Update(deltaTime);

	for (uint i = 0; i < indexAfterEntities; i++)
	{
		if (afterCameraUpdate[i]->GetActive())

			afterCameraUpdate[i]->Update(deltaTime);
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

	//Update(deltaTime);

	Render();


}

void Game::RemoveObservers()
{
	for (uint i = 0; i < spikes.GetCount(); i++)
		spikes[i].GetSubject()->RemoveObserver(healthBar);
	for (uint i = 0; i < boars.GetCount() / 2; i++)
		boars[i].GetSubject()->RemoveObserver(healthBar);
	for (uint i = 0; i < monkeys.GetCount(); i++)
		monkeys[i].GetSubject()->RemoveObserver(healthBar);
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
	case GLFW_KEY_S:
		input.shooting = false;
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
	case GLFW_KEY_S:
		input.shooting = true;
	default:
		break;
	}
}

void Game::AddPreEntity(Entity* entity)
{
	preCameraUpdate[indexPreEntities++] = entity;
}
void Game::AddAfterEntity(Entity* entity)
{
	afterCameraUpdate[indexAfterEntities++] = entity;
}

uint8_t Game::GetBitSpace(uint8_t& counts) const
{
	if (counts > sizeof(size_t))
		cout << "no more space'\n";
	return BitSpace * (counts++);
}


