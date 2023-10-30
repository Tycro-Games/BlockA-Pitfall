// Template, IGAD version 3
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2023

#include "precomp.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "lib/stb_image.h"

using namespace Tmpl8;

// Surface class implementation

Surface::Surface(int w, int h, uint* b) : pixels(b), width(w), height(h)
{
}

Surface::Surface(int w, int h) : width(w), height(h)
{
	pixels = (uint*)MALLOC64(w * h * sizeof(uint));
	ownBuffer = true; // needs to be deleted in destructor
}

Surface::Surface(const char* file) : pixels(0), width(0), height(0)
{
	// check if file exists; show an error if there is a problem
	FILE* f = fopen(file, "rb");
	if (!f) FatalError("File not found: %s", file);
	fclose(f);
	// load the file
	Surface::LoadFromFile(file);
}

void Surface::LoadFromFile(const char* file)
{
	// use stb_image to load the image file
	int n;
	unsigned char* data = stbi_load(file, &width, &height, &n, 0);
	if (!data) return; // load failed
	pixels = (uint*)MALLOC64(width * height * sizeof(uint));
	ownBuffer = true; // needs to be deleted in destructor
	const int s = width * height;
	if (n == 1) /* greyscale */
		for (int i = 0; i < s; i++)
		{
			const unsigned char p = data[i];
			pixels[i] = p + (p << 8) + (p << 16);
		}
	else
	{
		for (int i = 0; i < s; i++) pixels[i] = (data[i * n + 0] << 16) + (data[i * n + 1] << 8) + data[i * n + 2];
	}
	// free stb_image data
	stbi_image_free(data);
}

Surface::~Surface()
{
	if (ownBuffer)
		FREE64(pixels); // free only if we allocated the buffer ourselves
}

void Surface::Clear(uint c) const
{
	// WARNING: not the fastest way to do this.
	const int s = width * height;
	for (int i = 0; i < s; i++) pixels[i] = c;
}

void Surface::ClearOnlyNonTransparent(uint c)
{
	// WARNING: not the fastest way to do this.
	const int s = width * height;
	for (int i = 0; i < s; i++)
		if (pixels[i])
			pixels[i] = c;
}

void Surface::Plot(int x, int y, uint c)
{
	if (x < 0 || y < 0 || x >= width || y >= height) return;
	pixels[x + y * width] = c;
}

void Surface::Box(int x1, int y1, int x2, int y2, uint c)
{
	Line((float)x1, (float)y1, (float)x2, (float)y1, c);
	Line((float)x2, (float)y1, (float)x2, (float)y2, c);
	Line((float)x1, (float)y2, (float)x2, (float)y2, c);
	Line((float)x1, (float)y1, (float)x1, (float)y2, c);
}

//void Surface::Circle(int x1, int y1, float radius, uint c)
//{
//	const float2 start = { static_cast<float>(x1) ,static_cast<float>(y1)  };
//	for (int i = 0; i < 360; i++)
//	{
//		Plot(start.x + cos(i)*radius, start.y + sin(i)*(radius), c);
//	}
//
//}

void Surface::Bar(int x1, int y1, int x2, int y2, uint c)
{
	// clipping
	if (x1 < 0) x1 = 0;
	if (x2 >= width) x2 = width - 1;
	if (y1 < 0) y1 = 0;
	if (y2 >= height) y2 = width - 1;
	// draw clipped bar
	uint* a = x1 + y1 * width + pixels;
	for (int y = y1; y <= y2; y++)
	{
		for (int x = 0; x <= (x2 - x1); x++) a[x] = c;
		a += width;
	}
}


Surface8::Surface8(uint8_t w, uint8_t h)
{
	width = w;
	height = h;
	indexMap = new uint8_t[w * h];
	pal = new uint[256];
}


Surface8::Surface8(const char* csvPath, Surface* _pal)
{
	pal = new uint[_pal->width];
	uint* p = _pal->pixels;
	palCount = static_cast<uint8_t>(_pal->width);
	for (int i = 0; i < _pal->width; i++)
	{
		pal[i] = *p;
		p++;
	}

	//parse csv to index map
	//copy into a c style string
	char* tilemapString = new char[strlen(TextFileRead(csvPath).c_str()) + 1];
	strcpy(tilemapString, TextFileRead(csvPath).c_str());

	Tilemap::ExtractWidthHeight(tilemapString, width, height);
	indexMap = new uint8_t[width * height];

	char* startOfCsv = strstr(tilemapString, "csv\">\n") + strlen("csv\">\n");
	const char* pch = strtok(startOfCsv, ",");


	uint index = 0;
	while (*pch != '<') //stops when it reaches the end of the csv
	{
		uint numberForm = 0;
		Tilemap::ConvertCharToInt(pch, numberForm);
		indexMap[index++] = static_cast<uint8_t>(numberForm) - 1; //starts from 0
		pch = strtok(nullptr, ",\n");
	}

	delete[] tilemapString;
	delete _pal;
}

void Surface8::ToSurface(Surface* d, int mask) const
{
	uint* dst = d->pixels;
	for (uint i = 0; i < width * height; i++)
	{
		const uint8_t index = (indexMap[i] + palOffset) % palCount;
		if (*dst & mask)
			*dst = pal[index];
		dst++;
	}
}

void Surface8::Cycle()
{
	palOffset += 5; //when it reachers 256 is going to overflow to 1
}


Surface8::~Surface8()
{
	delete[] indexMap;
	delete[] pal;
}

// Surface::Print: Print some text with the hard-coded mini-font.
void Surface::Print(const char* s, int x1, int y1, uint c, const uint multiX, const uint multiY)
{
	if (!fontInitialized)
	{
		// we will initialize the font on first use
		InitCharset();
		fontInitialized = true;
	}
	uint* letterStart = pixels + x1 + y1 * width;
	for (int i = 0; i < static_cast<int>(strlen(s)); i++, letterStart += 6 * multiX)
	{
		int pos = 0;
		if ((s[i] >= 'A') && (s[i] <= 'Z')) pos = transl[static_cast<unsigned short>(s[i] - ('A' - 'a'))];
		else pos = transl[static_cast<unsigned short>(s[i])];
		uint* letterColumn = letterStart;
		//this variable looks like o::o:, it is always 5 characters per to be drawn per line of the character
		//it is always a combination of : and o
		//o means to write indexMap
		//: means to skip space
		const char* u = reinterpret_cast<const char*>(font[pos]);

		for (uint columns = 0; columns < 5; columns++)
		{
			//extra columns if we scale on Y
			for (uint extraColumns = 0; extraColumns < multiY; extraColumns++)
			{
				const char* copyU = u;

				for (uint rows = 0; rows < 5 * multiX; rows += multiX)
				{
					if (*copyU == 'o')
					{
						//extra row spaces if we scale on X
						for (uint extraRowSpaces = 0; extraRowSpaces < multiX; extraRowSpaces++)
						{
							*(letterColumn + rows + extraRowSpaces) = c;
							*(letterColumn + rows + width + extraRowSpaces) = 0;
						}
					}
					copyU++;
				}
				letterColumn += width;
			}
			//next line of the character
			u += 6;
			//add for extra space in between
			//a += width;
		}
	}
}

// Surface::Line: Draw a line between the specified screen coordinates.
// Uses clipping for lines that are partially off-screen. Not efficient.
void Surface::Line(float x1, float y1, float x2, float y2, uint c)
{
	// clip (Cohen-Sutherland, https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm)
	const float xmin = 0, ymin = 0, xmax = (float)width - 1, ymax = (float)height - 1;
	int c0 = OUTCODE(x1, y1), c1 = OUTCODE(x2, y2);
	bool accept = false;
	while (1)
	{
		if (!(c0 | c1))
		{
			accept = true;
			break;
		}
		if (c0 & c1) break;
		float x = 0, y = 0;
		const int co = c0 ? c0 : c1;
		if (co & 8) x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1), y = ymax;
		else if (co & 4) x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1), y = ymin;
		else if (co & 2) y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1), x = xmax;
		else if (co & 1) y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1), x = xmin;
		if (co == c0) x1 = x, y1 = y, c0 = OUTCODE(x1, y1);
		else x2 = x, y2 = y, c1 = OUTCODE(x2, y2);
	}
	if (!accept) return;
	float b = x2 - x1, h = y2 - y1, l = fabsf(b);
	if (fabsf(h) > l) l = fabsf(h);
	int il = (int)l;
	float dx = b / (float)l, dy = h / (float)l;
	for (int i = 0; i <= il; i++, x1 += dx, y1 += dy)
		*(pixels + (int)x1 + (int)y1 * width) = c;
}

void Surface::BezierCurve(uint col, const float2& a, const float2& b, const float2& c, const float2& d,
                          uint resolution = 50)
{
	float2 startPoint = a;
	for (uint i = 1; i <= resolution; i++)
	{
		const float2 point = MathLibrary::CubicBezierCurve(a, b, c, d,
		                                                   static_cast<float>(i) / static_cast<float>(resolution));

		Line(startPoint.x, startPoint.y, point.x, point.y, col);
		startPoint = point;
	}
}

// Surface::CopyTo: Copy the contents of one Surface to another, at the specified
// location. With clipping.
void Surface::CopyTo(Surface* d, int x, int y)
{
	uint* dst = d->pixels;
	uint* src = pixels;
	if ((src) && (dst))
	{
		int srcwidth = width;
		int srcheight = height;
		int dstwidth = d->width;
		int dstheight = d->height;
		if ((srcwidth + x) > dstwidth) srcwidth = dstwidth - x;
		if ((srcheight + y) > dstheight) srcheight = dstheight - y;
		if (x < 0) src -= x, srcwidth += x, x = 0;
		if (y < 0) src -= y * srcwidth, srcheight += y, y = 0;
		if ((srcwidth > 0) && (srcheight > 0))
		{
			dst += x + dstwidth * y;
			for (int i = 0; i < srcheight; i++)
			{
				memcpy(dst, src, srcwidth * 4);
				dst += dstwidth, src += width;
			}
		}
	}
}

void Surface::SetChar(int c, const char* c1, const char* c2, const char* c3, const char* c4, const char* c5)
{
	strcpy(font[c][0], c1);
	strcpy(font[c][1], c2);
	strcpy(font[c][2], c3);
	strcpy(font[c][3], c4);
	strcpy(font[c][4], c5);
}

void Surface::InitCharset()
{
	SetChar(0, ":ooo:", "o:::o", "ooooo", "o:::o", "o:::o");
	SetChar(1, "oooo:", "o:::o", "oooo:", "o:::o", "oooo:");
	SetChar(2, ":oooo", "o::::", "o::::", "o::::", ":oooo");
	SetChar(3, "oooo:", "o:::o", "o:::o", "o:::o", "oooo:");
	SetChar(4, "ooooo", "o::::", "oooo:", "o::::", "ooooo");
	SetChar(5, "ooooo", "o::::", "ooo::", "o::::", "o::::");
	SetChar(6, ":oooo", "o::::", "o:ooo", "o:::o", ":ooo:");
	SetChar(7, "o:::o", "o:::o", "ooooo", "o:::o", "o:::o");
	SetChar(8, "::o::", "::o::", "::o::", "::o::", "::o::");
	SetChar(9, ":::o:", ":::o:", ":::o:", ":::o:", "ooo::");
	SetChar(10, "o::o:", "o:o::", "oo:::", "o:o::", "o::o:");
	SetChar(11, "o::::", "o::::", "o::::", "o::::", "ooooo");
	SetChar(12, "oo:o:", "o:o:o", "o:o:o", "o:::o", "o:::o");
	SetChar(13, "o:::o", "oo::o", "o:o:o", "o::oo", "o:::o");
	SetChar(14, ":ooo:", "o:::o", "o:::o", "o:::o", ":ooo:");
	SetChar(15, "oooo:", "o:::o", "oooo:", "o::::", "o::::");
	SetChar(16, ":ooo:", "o:::o", "o:::o", "o::oo", ":oooo");
	SetChar(17, "oooo:", "o:::o", "oooo:", "o:o::", "o::o:");
	SetChar(18, ":oooo", "o::::", ":ooo:", "::::o", "oooo:");
	SetChar(19, "ooooo", "::o::", "::o::", "::o::", "::o::");
	SetChar(20, "o:::o", "o:::o", "o:::o", "o:::o", ":oooo");
	SetChar(21, "o:::o", "o:::o", ":o:o:", ":o:o:", "::o::");
	SetChar(22, "o:::o", "o:::o", "o:o:o", "o:o:o", ":o:o:");
	SetChar(23, "o:::o", ":o:o:", "::o::", ":o:o:", "o:::o");
	SetChar(24, "o:::o", "o:::o", ":oooo", "::::o", ":ooo:");
	SetChar(25, "ooooo", ":::o:", "::o::", ":o:::", "ooooo");
	SetChar(26, ":ooo:", "o::oo", "o:o:o", "oo::o", ":ooo:");
	SetChar(27, "::o::", ":oo::", "::o::", "::o::", ":ooo:");
	SetChar(28, ":ooo:", "o:::o", "::oo:", ":o:::", "ooooo");
	SetChar(29, "oooo:", "::::o", "::oo:", "::::o", "oooo:");
	SetChar(30, "o::::", "o::o:", "ooooo", ":::o:", ":::o:");
	SetChar(31, "ooooo", "o::::", "oooo:", "::::o", "oooo:");
	SetChar(32, ":oooo", "o::::", "oooo:", "o:::o", ":ooo:");
	SetChar(33, "ooooo", "::::o", ":::o:", "::o::", "::o::");
	SetChar(34, ":ooo:", "o:::o", ":ooo:", "o:::o", ":ooo:");
	SetChar(35, ":ooo:", "o:::o", ":oooo", "::::o", ":ooo:");
	SetChar(36, "::o::", "::o::", "::o::", ":::::", "::o::");
	SetChar(37, ":ooo:", "::::o", ":::o:", ":::::", "::o::");
	SetChar(38, ":::::", ":::::", "::o::", ":::::", "::o::");
	SetChar(39, ":::::", ":::::", ":ooo:", ":::::", ":ooo:");
	SetChar(40, ":::::", ":::::", ":::::", ":::o:", "::o::");
	SetChar(41, ":::::", ":::::", ":::::", ":::::", "::o::");
	SetChar(42, ":::::", ":::::", ":ooo:", ":::::", ":::::");
	SetChar(43, ":::o:", "::o::", "::o::", "::o::", ":::o:");
	SetChar(44, "::o::", ":::o:", ":::o:", ":::o:", "::o::");
	SetChar(45, ":::::", ":::::", ":::::", ":::::", ":::::");
	SetChar(46, "ooooo", "ooooo", "ooooo", "ooooo", "ooooo");
	SetChar(47, "::o::", "::o::", ":::::", ":::::", ":::::"); // Tnx Ferry
	SetChar(48, "o:o:o", ":ooo:", "ooooo", ":ooo:", "o:o:o");
	SetChar(49, "::::o", ":::o:", "::o::", ":o:::", "o::::");
	char c[] = "abcdefghijklmnopqrstuvwxyz0123456789!?:=,.-() #'*/";
	int i;
	for (i = 0; i < 256; i++) transl[i] = 45;
	for (i = 0; i < 50; i++) transl[(unsigned char)c[i]] = i;
}
