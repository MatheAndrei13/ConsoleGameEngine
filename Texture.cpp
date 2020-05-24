#include "Texture.h"

Texture::Texture() {
	buffer = nullptr;
	size = { 0, 0 };
}
Texture::~Texture() {
	Destroy();
}

void Texture::operator=(const Texture& tex) {
	// Return If Same Texture
	if (this == &tex)
		return;

	// Destroy Previous Texture
	Destroy();

	// Allocate Memory to Buffer
	buffer = new CHAR_INFO[tex.size.X * tex.size.Y];
	size = tex.size;

	// Reset Buffer
	memset(buffer, NULL, sizeof(CHAR_INFO) * size.X * size.Y);

	for (short x = 0; x < tex.size.X; ++x)
		for (short y = 0; y < tex.size.Y; ++y)
			buffer[x + size.X * y] = tex.buffer[x + size.X * y];
}

void Texture::Create(short width, short height) {
	// Destroy Previous Texture
	Destroy();

	// Allocate Memory to Buffer
	buffer = new CHAR_INFO[width * height];
	size = { width, height };

	// Reset Buffer
	memset(buffer, NULL, sizeof(CHAR_INFO) * size.X * size.Y);
}
void Texture::Destroy() {
	// Delete Buffer If Not Empty
	if (buffer != nullptr)
		delete[] buffer;
	size = { 0, 0 };
}

COORD Texture::GetSize() const {
	return size;
}

// TOOLS
bool Texture::OutOfBounds(short x, short y) const {
	return (x < 0 || y < 0) || (x >= size.X || y >= size.Y);
}
void Texture::SetPixel(short x, short y, wchar_t glyph, unsigned char color) {
	if (OutOfBounds(x, y))
		return;

	buffer[x + size.X * y].Char.UnicodeChar = glyph;
	buffer[x + size.X * y].Attributes = color;
}
void Texture::Fill(short x0, short y0, short x1, short y1, wchar_t glyph, unsigned char color) {
	for (int x = x0; x <= x1; ++x)
		for (int y = y0; y <= y1; ++y)
			SetPixel(x, y, glyph, color);
}