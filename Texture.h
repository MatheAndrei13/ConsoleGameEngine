#pragma once
#include <Windows.h>

class Display;
class GameManager;

class Texture {
	CHAR_INFO* buffer;
	COORD size;

	friend class Display;
	friend class GameManager;

public:
	Texture();
	~Texture();

	void operator=(const Texture&);

	void Create(short width, short height);
	void Destroy();

	COORD GetSize() const;

	// TOOLS
	bool OutOfBounds(short x, short y) const;
	void SetPixel(short x, short y, wchar_t glyph, unsigned char color);
	void Fill(short x0, short y0, short x1, short y1, wchar_t glyph, unsigned char color);
};

