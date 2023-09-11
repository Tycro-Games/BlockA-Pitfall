// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#pragma once

#include "Scripts/Player/Avatar.h"
#include "Scripts/Tilemap/Tilemap.h"
namespace Tmpl8
{
	enum TilemapType
	{
		BG,
		FLOOR,
		COUNT
	};

	class Game : public TheApp
	{
	public:

		// game flow methods
		void Init();
		void Render();
		void Update(float deltaTime);
		void UpdateInput();
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
		

		Tilemap tilemaps[COUNT];
		bool TilemapMoves();
		Avatar avatar;
		//input
		int horizontalMove = 0;
		int verticalMove = 0;
		
	};

} // namespace Tmpl8