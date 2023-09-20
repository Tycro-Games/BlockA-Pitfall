// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#pragma once


namespace Tmpl8
{
	enum TilemapType
	{
		PARALLAX,
		BG,
		FLOOR,
		LADDERS,
		COUNT
	};

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
		void Shutdown() { /* implement if you want to do something on exit */ }
		// input handling
		void MouseUp(int) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
		void MouseWheel(float) { /* implement if you want to handle the mouse wheel */ }
		void KeyUp(int);
		void KeyDown(int);
		// data members
		int2 mousePos;
		//entities
		Sprite* enviroment;
		Sprite* parallaxSprite;
		Camera cam;
		Tilemap tilemaps[COUNT];
		Avatar avatar;
		//input
		int horizontalMove = 0;
		int verticalMove = 0;
		bool isJumping = false;
		const float fixedDeltaTime = 0.02f;
	};

} // namespace Tmpl8