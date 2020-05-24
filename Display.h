#pragma once
#include <Windows.h>
#include <string>
#include "GameManager.h"

class Game;
class Input;
class Texture;

class Display {
	HWND consoleWindow;
	HANDLE handleIn;
	HANDLE handleOut;
	SMALL_RECT windowSize;
	COORD screenSize;
	COORD fontSize;

	CONSOLE_SCREEN_BUFFER_INFOEX sbInfo;
	CONSOLE_FONT_INFOEX fontInfo;
	CONSOLE_CURSOR_INFO cursorInfo;
	LONG windowStyle;
	DWORD consoleMode;
	DEVMODE displaySettings;

	struct SCREEN_BUFFER {
		CHAR_INFO* buffer;
		COORD size;
		COORD position;
		SMALL_RECT region;

		SCREEN_BUFFER();
		~SCREEN_BUFFER();
		void Init(short width, short height);
	} screenBuffer;

private:
	Display();
	Display(const Display&) = delete;

	void Init(std::wstring Title, short screenWidth, short screenHeight, short fontWidth, short fontHeight);

	void DrawBuffer();
	void WriteToBuffer(short x, short y, Texture const& tex);

	HANDLE& GetInputHandle();
	HANDLE& GetOutputHandle();

	friend class Game;
	friend class Input;
	friend void GameManager::DrawGameObjects() const;

public:
	static Display& Get();

	void Clear();
	void SetTitle(std::wstring title);
	int DisplayFrequency() const;
	COORD GetSize() const;
};

