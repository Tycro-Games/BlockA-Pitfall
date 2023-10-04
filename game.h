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

		~Game();
		void AddObservers();
		void SetUpCamera();
		void AddAllEntities();
		// game flow methods
		void Init();
		void RenderUI();
		void Render();
		void Update(float deltaTime);
		void UpdateInput();
		void FixedUpdate(float deltaTime);
		void Tick(float deltaTime);
		void RemoveObservers();
		void Shutdown();
		// input handling
		void MouseUp(int) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
		void MouseWheel(float wheelDirection){};
		void KeyUp(int);
		void KeyDown(int);
		void AddPreEntity(Entity& entity);
		void AddAfterEntity(Entity& entity);
		// data members
		int2 mousePos;
		//preCamera
		Sprite* enviroment;
		Sprite* parallaxSprite;
		Camera cam;
		Tilemap tileMaps[Tilemap::COUNT];
		SpawnNonTiles nonTiles[SpawnNonTiles::COUNT];
		size_t countRopes;
		size_t countSpikes;
		size_t countZiplines;
		size_t countBoars;
		Rope* ropes = nullptr;
		Zipline* ziplines = nullptr;
		Spike* spikes = nullptr;
		Boar* boars = nullptr;
		Avatar avatar;
		//UI
		HealthBar healthBar;
		//Update and rendering

		Entity* preCamera[MAX_ENTITIES_NUMBER];
		Entity* afterCamera[MAX_ENTITIES_NUMBER];
		uint indexPreEntities = 0;
		uint indexAfterEntities = 0;
		//input
		Input input;

	};

} // namespace Tmpl8