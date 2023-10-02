// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#pragma once


namespace Tmpl8
{


	class Game : public TheApp
	{
	public:

		~Game();
		// game flow methods
		void Init();
		void Render();
		void Update(float deltaTime);
		void UpdateInput();
		void FixedUpdate(float deltaTime);
		void Tick(float deltaTime);
		void Shutdown();
		// input handling
		void MouseUp(int) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
		void MouseWheel(float wheelDirection){};
		void KeyUp(int);
		void KeyDown(int);
		// data members
		int2 mousePos;
		//entities
		Sprite* enviroment;
		Sprite* parallaxSprite;
		Camera cam;
		Tilemap tileMaps[Tilemap::COUNT];
		SpawnNonTiles nonTiles[SpawnNonTiles::COUNT];
		size_t countRopes;
		size_t countZiplines;
		Rope* ropes = nullptr;
		Zipline* ziplines = nullptr;
		Avatar avatar;
	

		//input
		Input input;
		/*int horizontalMove = 0;
		int verticalMove = 0;
		bool isJumping = false;*/
	};

} // namespace Tmpl8