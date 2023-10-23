// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"
#include "game.h"
//only once
Game::Game()
{
	music.setLooping(true);
	music.setStartTime(0);
	InitTiles();
	InitEntities();
	AddAllEntities();
	SetUpCamera();

	healthBar.Init("assets/heart_animated_1.png");
	avatar = new Avatar("assets/PlayerSheet/PlayerBase/Character Idle 48x48.png",
	                    tileMaps[Tilemap::FLOOR], tileMaps[Tilemap::LADDERS],
	                    ropes, ziplines, elasticPlants, coins, cam);
	avatar->Init();
	AddEntity(avatar);

	AddObservers();
	//init the text
	menuTextAnimation = new Surface8("assets/TextColorCycling.tmx", new Surface("assets/FireColor.png"));
	menuText = new Surface(960, 60);
	colorCycle = new Surface(960, 60);
	menuText->Clear(0);
	menuText->Print("Press any key to start the game!", 0, 0, WHITE);
	menuText->Print("except escape...", 0, 30, WHITE);
}


void Game::AddObservers()
{
	for (uint i = 0; i < spikes.GetCount(); i++)
		spikes[i].GetSubject()->AddObserver(healthBar);
	for (uint i = 0; i < boars.GetCount(); i++)
	{
		boars[i].GetSubject()->AddObserver(healthBar);
		boars[i].GetSubject()->AddObserver(score);
		boars[i].GetSubject()->AddObserver(winCondition);
	}
	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		monkeys[i].GetSubject()->AddObserver(healthBar);
		monkeys[i].GetSubject()->AddObserver(score);
		monkeys[i].GetSubject()->AddObserver(winCondition);
	}

	for (uint i = 0; i < coins.GetCount(); i++)
	{
		coins[i].GetSubject()->AddObserver(coinScore);
		coins[i].GetSubject()->AddObserver(score);
	}
	winCondition.GetSubject()->AddObserver(gameState);
	avatar->GetSubject()->AddObserver(cam);

	healthBar.GetSubject()->AddObserver(*avatar);
	healthBar.GetSubject()->AddObserver(gameState);
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
	for (int i = Tilemap::BG; i < Tilemap::COUNT; i++)
	{
		tileMaps[i].Render(enviroment->GetSurface());
	}
	tileMaps[Tilemap::PARALLAX].Render(parallaxSprite->GetSurface());

#ifdef _DEBUG
	tileMaps[Tilemap::FLOOR].DebugBox(enviroment->GetSurface());
#endif

	cam.Init(enviroment, parallaxSprite);
	cam.SetPosition(STARTING_POSITION);
}

void Game::AddAllEntities()
{
	for (uint i = 0; i < ziplines.GetCount(); i++)
	{
		AddEntity(&ziplines[i]);
	}
	for (uint i = 0; i < ropes.GetCount(); i++)
	{
		AddEntity(&ropes[i]);
	}
	for (uint i = 0; i < elasticPlants.GetCount(); i++)
	{
		AddEntity(&elasticPlants[i]);
	}
	for (uint i = 0; i < coins.GetCount(); i++)
	{
		AddEntity(&coins[i]);
	}
	for (uint i = 0; i < spikes.GetCount(); i++)
	{
		AddEntity(&spikes[i]);
	}
	for (uint i = 0; i < boars.GetCount(); i++)
	{
		AddEntity(&boars[i]);
	}
	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		AddEntity(&monkeys[i]);
	}
}

void Game::InitPositionEntities()
{
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
	for (uint i = 0; i < coins.GetCount(); i++)
	{
		coins[i].Init(nonTiles[SpawnNonTiles::COINS].GetPosition(i));
	}
	for (uint i = 0; i < spikes.GetCount(); i++)
	{
		spikes[i].Init(nonTiles[SpawnNonTiles::SPIKES].GetPosition(i), *avatar);
	}
	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		monkeys[i].Init(nonTiles[SpawnNonTiles::MONKEYS].GetPosition(i), &tileMaps[Tilemap::FLOOR],
		                &tileMaps[Tilemap::LADDERS], *avatar);
	}
	zIndex = 0;

	for (uint i = 0; i < boars.GetCount() * 2; i += 2)
	{
		boars[zIndex].Init(nonTiles[SpawnNonTiles::BOARS].GetPosition(i),
		                   nonTiles[SpawnNonTiles::BOARS].GetPosition(i + 1)
		                   , *avatar);
	}
}

//TODO refactor so it is more easy to use
void Game::InitEntities()
{
	//used as reference https://www.3dgep.com/cpp-fast-track-9-colours/
	uint8_t countEnemies = 0;
	uint8_t countStatics = 0;
	size_t countProps = nonTiles[SpawnNonTiles::ROPE].GetCount() << GetBitSpace(countStatics);
	countProps = countProps | nonTiles[SpawnNonTiles::ZIPLINE].GetCount() << GetBitSpace(countStatics);
	countProps = countProps | nonTiles[SpawnNonTiles::ELASTIC_PLANTS].GetCount() << GetBitSpace(countStatics);
	countProps = countProps | nonTiles[SpawnNonTiles::COINS].GetCount() << GetBitSpace(countStatics);

	size_t countsEnemies = nonTiles[SpawnNonTiles::SPIKES].GetCount() << GetBitSpace(countEnemies);
	countsEnemies = countsEnemies | nonTiles[SpawnNonTiles::BOARS].GetCount() << GetBitSpace(countEnemies);
	countsEnemies = countsEnemies | nonTiles[SpawnNonTiles::MONKEYS].GetCount() << GetBitSpace(countEnemies);

	countEnemies = 1;
	countStatics = 1;

	size_t count = countProps & 0b11111111; //255 in binary
	ropes.Init(count);


	uint8_t shift = GetBitSpace(countStatics);
	count = (countProps & 0b11111111 << shift) >> shift;
	ziplines.Init(count);

	shift = GetBitSpace(countStatics);
	count = (countProps & 0b11111111 << shift) >> shift;
	elasticPlants.Init(count);

	shift = GetBitSpace(countStatics);
	count = (countProps & 0b11111111 << shift) >> shift;
	coins.Init(count);

	count = countsEnemies & 0b11111111;
	spikes.Init(count);

	shift = GetBitSpace(countEnemies);
	count = (countsEnemies & 0b11111111 << shift) >> shift;

	boars.Init(count);

	shift = GetBitSpace(countEnemies);
	count = (countsEnemies & 0b11111111 << shift) >> shift;
	monkeys.Init(count);


	for (uint i = 0; i < monkeys.GetCount(); i++)
	{
		/*	monkeys[i].Init(nonTiles[SpawnNonTiles::MONKEYS].GetPosition(i), &tileMaps[Tilemap::FLOOR],
				&tileMaps[Tilemap::LADDERS], avatar);*/
		winCondition.AddEnemy(&monkeys[i]);
	}
	uint zIndex = 0;
	for (uint i = 0; i < boars.GetCount() * 2; i += 2)
	{
		winCondition.AddEnemy(&boars[zIndex++]);
	}
}

void Game::InitTiles()
{
	tileMaps[Tilemap::PARALLAX].Init("assets/Pitfall_tilesheet.png", "assets/Parallax.tmx");
	tileMaps[Tilemap::BG].Init("assets/Basic Tilemap.png", "assets/Tilemap.tmx");
	tileMaps[Tilemap::FLOOR].Init("assets/160x160 background tilemap.png", "assets/Floors.tmx");
	tileMaps[Tilemap::LADDERS].Init("assets/Pitfall_tilesheet.png", "assets/Ladders.tmx");
	//non tiles
	bool hasPairOfTwoPositions = true;
	nonTiles[SpawnNonTiles::ROPE].Init("assets/Ropes.tmx");
	nonTiles[SpawnNonTiles::ZIPLINE].Init("assets/Ziplines.tmx", hasPairOfTwoPositions);
	nonTiles[SpawnNonTiles::ELASTIC_PLANTS].Init("assets/ElasticPlants.tmx");
	nonTiles[SpawnNonTiles::COINS].Init("assets/Coins.tmx");
	//enemies
	nonTiles[SpawnNonTiles::SPIKES].Init("assets/Spikes.tmx");
	nonTiles[SpawnNonTiles::MONKEYS].Init("assets/Monkeys.tmx");
	nonTiles[SpawnNonTiles::BOARS].Init("assets/Boars.tmx", hasPairOfTwoPositions);
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	InitPositionEntities();
	score.SetPoints(0);
	coinScore.SetPoints(0);
	healthBar.Init();
	//TODO SAVE CHECKPOINT
	cam.SetPosition(STARTING_POSITION);
	avatar->Init();
	music.play();
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
	switch (gameState.GetState())
	{
	case GameStateManager::PLAYING:
		//clean the surfaces
		screen->Clear(0);
		cam.CleanPreRenderSurface();

	//first to call
		cam.RenderTilemaps();

		for (uint i = 0; i < indexPreEntities; i++)
		{
			if (preCameraUpdate[i]->IsActive())
				preCameraUpdate[i]->Render(cam.pGetPreRender());
		}

	//screen->Print();

		cam.Render(screen);

		RenderUI();
		break;
	case GameStateManager::LOSE:
		music.replay();
		Init();
		gameState.SetState(GameStateManager::PLAYING);

		break;
	case GameStateManager::WIN:
		screen->Clear(0);
		screen->Print("You killed all the enemies, ", SMALL_PADDING, SMALL_PADDING, RED);
		screen->Print("so you win!", SMALL_PADDING, HALF_SCRHEIGHT, RED);
		screen->Print("Press escape to quit.", SMALL_PADDING, HALF_SCRHEIGHT + SMALL_PADDING, RED);
		break;
	case GameStateManager::START_MENU:
		screen->Clear(0);

		menuTextAnimation->ToSurface(menuText, TEXT_MASK);

		menuText->CopyTo(screen, SMALL_PADDING, HALF_SCRHEIGHT);
		menuTextAnimation->Cycle();


		break;
	default: ;
	}
}


void Game::UpdateInput()
{
	avatar->SetInput(input.arrowKeys);

	avatar->SetJumpInput(input.jumping);
	avatar->SetShootInput(input.shooting);
}


void Game::FixedUpdate(float deltaTime)
{
	switch (gameState.GetState())
	{
	case GameStateManager::PLAYING:

		for (uint i = 0; i < indexPreEntities; i++)
		{
			if (preCameraUpdate[i]->IsActive())

				preCameraUpdate[i]->Update(deltaTime);
		}
	//camera position also gets updated
		cam.Update(deltaTime);


		break;
	case GameStateManager::LOSE:
		music.stop();
		break;
	case GameStateManager::WIN:
		break;
	case GameStateManager::START_MENU:
		break;
	default: break;
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

	if (fixedTimer.elapsed() > fixedDeltaTime)
	{
		fixedTimer.reset();
		FixedUpdate(fixedDeltaTime);
	}

	//Update(deltaTime);

	Render();
}

void Game::Shutdown()
{
	//remove observers

	delete enviroment;
	delete parallaxSprite;
	delete avatar;

	delete menuText;
	delete menuTextAnimation;
	delete colorCycle;
}

//this is called automatically now
//void Game::MouseWheel(float wheelDirection)
//{
//	cam.SetInputScaling(wheelDirection);
//}

void Game::KeyUp(int key)
{
	if (gameState.GetState() == GameStateManager::START_MENU)
	{
		input.arrowKeys = 0;
		input.shooting = false;
		input.smallJump = false;
		input.jumping = false;
		gameState.SetState(GameStateManager::PLAYING);
		return;
	}
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
	//is we are in the start menu we can start the game if the player presses something

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

void Game::AddEntity(Entity* entity)
{
	preCameraUpdate[indexPreEntities++] = entity;
}


uint8_t Game::GetBitSpace(uint8_t& counts) const
{
	if (counts > sizeof(size_t))
		cout << "no more space'\n";
	return BitSpace * (counts++);
}
