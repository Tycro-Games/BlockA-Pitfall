// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"

#include <iostream>

using namespace Tmpl8;

// constructor
Sprite::Sprite(Surface* surface, unsigned int frameCount) :
	width(surface->width / frameCount),
	height(surface->height),
	numFrames(frameCount),
	currentFrame(0),
	flags(0),
	start(new unsigned int*[frameCount]),
	surface(surface)
{
	InitializeStartData();
}

// destructor
Sprite::~Sprite()
{
	delete surface;
	for (unsigned int i = 0; i < numFrames; i++) delete start[i];
	delete start;
}

// draw sprite to target surface
void Sprite::Draw(Surface* target, int x, int y)
{
	if (x < -width || x > (target->width + width)) return;
	if (y < -height || y > (target->height + height)) return;

	int x1 = x, x2 = x + width;
	int y1 = y, y2 = y + height;
	uint* src = GetBuffer() + currentFrame * width;

	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	int xs;
	if (x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * target->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - y);


			const int lsx = start[currentFrame][line] + x; //template optimization
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				const uint c1 = *(src + i);
				if (c1 & 0xffffff) *(dest + addr + i) = c1; //checks for a non-empty pixel
			}
			addr += target->width;
			src += width * numFrames;
		}
	}
}

// draw sprite to target surface
void Sprite::DrawFlippedX(Surface* target, int x, int y)
{
	if (x < -width || x > (target->width + width)) return;
	if (y < -height || y > (target->height + height)) return;

	int x1 = x + width, x2 = x;
	int y1 = y, y2 = y + height;
	uint* src = GetBuffer() + currentFrame * width + width;
	if (x2 < 0) src += x2, x2 = 0;
	if (x1 > target->width) x1 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	if (x1 > x2 && y2 > y1)
	{
		uint address = y1 * target->width + x2;
		const int w = x1 - x2;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				const uint c1 = *(src - i);
				if (c1 & 0xffffff)
					*(dest + address + i) = c1; //checks for a non-empty pixel
			}
			//next line
			address += target->width;
			src += width * numFrames;
		}
	}
}

// draw scaled sprite
//help from matt Y3
void Sprite::DrawScaled(int x1, int y1, int w, int h, Surface* target)
{
	//added bound checking from Draw
	int x2 = x1 + w;
	int y2 = y1 + h;
	if (x1 < -w || x1 > target->width) return;
	if (y1 < -h || y1 > target->height) return;

	uint* src = GetBuffer() + currentFrame * width;
	int maxAddY = 0;
	int maxAddX = 0;
	int minAddX = 0;
	int minAddY = 0;

	if (x1 < 0)
		minAddX = -x1;
	if (x2 > target->width)
		maxAddX = x2 - target->width;
	if (y1 < 0)
		minAddY = -y1;
	if (y2 > target->height)
		maxAddY = y2 - target->height;


	const float divX = 1.0f / static_cast<float>(w);
	const float divY = 1.0f / static_cast<float>(h);


	if (width == 0 || height == 0) return;
	for (int x = minAddX; x < w - maxAddX; x++)
	{
		const int u = static_cast<int>(static_cast<float>(x) *
			(static_cast<float>(width) * divX));
		for (int y = minAddY; y < h - maxAddY; y++)
		{
			const int v = static_cast<int>(static_cast<float>(y) *
				(static_cast<float>(height) * divY));

			const uint color = src[u + v * width * numFrames];
			if (color & 0xffffff) target->pixels[x1 + x + ((y1 + y) * target->width)] = color;
		}
	}
}

// prepare sprite outline data for faster rendering
void Sprite::InitializeStartData()
{
	for (unsigned int f = 0; f < numFrames; ++f)
	{
		start[f] = new unsigned int[height];

		for (int y = 0; y < height; ++y)
		{
			start[f][y] = width;
			uint* addr = GetBuffer() + f * width + y * width * numFrames;
			for (int x = 0; x < width; ++x)
				if (addr[x])
				{
					start[f][y] = x;
					break;
				}
		}
	}
}
