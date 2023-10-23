// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#pragma once


namespace Tmpl8
{
	constexpr uint MAX_ENTITIES_NUMBER = 100;

	class Game : public TheApp
	{
	public:
		Game();
		~Game() override = default;
		void AddObservers();
		void SetUpCamera();
		void AddAllEntities();
		void InitPositionEntities();
		void InitEntities();
		void InitTiles();
		// game flow methods
		void Init() override;
		void RenderUI();
		void Render();
		//void Update(float deltaTime);
		void UpdateInput();
		void FixedUpdate(float deltaTime);
		void Tick(float deltaTime) override;
		void Shutdown() override;
		// input handling
		void MouseUp(int) override
		{
			/* implement if you want to detect mouse button presses */
		}

		void MouseDown(int) override
		{
			/* implement if you want to detect mouse button presses */
		}

		void MouseMove(int x, int y) override
		{
			mousePos.x = x, mousePos.y = y;
		}

		void MouseWheel(float) override
		{
		}

		void KeyUp(int) override;
		void KeyDown(int) override;
		void AddEntity(Entity* entity);
		uint8_t GetBitSpace(uint8_t& counts) const;
		// data members
		int2 mousePos;
		//preCameraUpdate
		Sprite* enviroment;
		Sprite* parallaxSprite;
		Camera cam;
		Tilemap tileMaps[Tilemap::COUNT];
		SpawnNonTiles nonTiles[SpawnNonTiles::COUNT];

		const uint8_t BitSpace = 8;

		Array<Rope> ropes;
		Array<Zipline> ziplines;
		Array<ElasticPlant> elasticPlants;
		Array<Coin> coins;
		//will add elastic plants

		Array<Spike> spikes;
		Array<Boar> boars;
		Array<Monkey> monkeys;

		Avatar* avatar = nullptr;
		//UI
		HealthBar healthBar;
		PlayerScore score;
		CoinScore coinScore;
		Surface* menuText = nullptr;
		Surface* colorCycle = nullptr;
		Surface8* menuTextAnimation = nullptr;
		const int menuTextWidth = 960;
		const int menuTextHeight = 60;
		const int TEXT_MASK = 0x00ffffff;
		//Update and rendering

		Entity* preCameraUpdate[MAX_ENTITIES_NUMBER] = {};
		uint indexPreEntities = 0;
		//win condition
		WinCondition winCondition;
		GameStateManager gameState;
		const int SMALL_PADDING = 100;
		const int OVER_HALF_SCREEN_Y = 434;
		//music
		Audio::Sound music{"assets/Audio/Fur Elise (by Beethoven) - Beethoven.mp3", Audio::Sound::Type::Stream};
		//input
		Input input;
		const float2 STARTING_POSITION = {0, 0};
	};
} // namespace Tmpl8
