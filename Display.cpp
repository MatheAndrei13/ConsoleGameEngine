#include "Display.h"
#include "Texture.h"

Display::Display() {
	// Get Console Window
	consoleWindow = GetConsoleWindow();

	// Get Handles
	handleIn = GetStdHandle(STD_INPUT_HANDLE);
	handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get Console Screen Buffer Info
	GetConsoleScreenBufferInfoEx(handleOut, &sbInfo);

	// Get Console Font Info
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(handleOut, FALSE, &fontInfo);

	// Get Console Cursor Info
	GetConsoleCursorInfo(handleOut, &cursorInfo);
	
	// Get Window Style
	windowStyle = GetWindowLong(consoleWindow, GWL_STYLE);

	// Get Console Mode
	GetConsoleMode(handleIn, &consoleMode);

	// Get Display Settings
	displaySettings.dmSize = sizeof(DEVMODE);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &displaySettings);

	// Get Default Window Size
	windowSize = sbInfo.srWindow;

	// Get Default Screen Size
	screenSize = sbInfo.dwSize;

	// Get Default Font Size
	fontSize = fontInfo.dwFontSize;
}
Display& Display::Get() {
	static Display consoleDisplay;
	return consoleDisplay;
}

void Display::Init(std::wstring title, short screenWidth, short screenHeight, short fontWidth, short fontHeight) {
	// Set Console Title
	SetConsoleTitle(title.c_str());

	// Set Font Style
	fontInfo.nFont = 0;
	fontInfo.dwFontSize = COORD({ fontWidth, fontHeight });
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(handleOut, FALSE, &fontInfo);

	// Check If Sizes Are Valid
	COORD largestWindowSize = GetLargestConsoleWindowSize(handleOut);
	if (largestWindowSize.X < screenWidth || largestWindowSize.Y < screenHeight)
		SetConsoleTitle(L"INVALID SIZES");
	
	// Reset Window Size
	windowSize = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(handleOut, TRUE, &windowSize);

	// Set Screen Buffer Size
	screenSize = { screenWidth, screenHeight };
	SetConsoleScreenBufferSize(handleOut, screenSize);

	// Set Window Size
	windowSize = { 0, 0, screenWidth - 1, screenHeight - 1 };
	SetConsoleWindowInfo(handleOut, TRUE, &windowSize);

	// Disable Maximizing & Resizing Window Events
	SetWindowLong(consoleWindow, GWL_STYLE, windowStyle & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	// Disable Mouse & Keyboard Edit Mode
	SetConsoleMode(handleIn, consoleMode & ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

	// Hide Console Cursor
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handleOut, &cursorInfo);

	// Set Screen Buffer
	screenBuffer.Init(screenWidth, screenHeight);
}

Display::SCREEN_BUFFER::SCREEN_BUFFER() {
	buffer = nullptr;
	size = { 0, 0 };
	position = { 0, 0 };
	region = { 0, 0, 0, 0 };
}
Display::SCREEN_BUFFER::~SCREEN_BUFFER() {
	if (buffer != nullptr)
		delete[] buffer;
	size = { 0, 0 };
}
void Display::SCREEN_BUFFER::Init(short width, short height) {
	buffer = new CHAR_INFO[width * height];
	size = { width, height };
	position = { 0, 0 };
	region = { 0, 0, width - 1, height - 1 };
	
	// Reset Buffer
	memset(buffer, NULL, sizeof(CHAR_INFO) * size.X * size.Y);
}

void Display::DrawBuffer() {
	WriteConsoleOutput(handleOut, screenBuffer.buffer, screenBuffer.size, screenBuffer.position, &screenBuffer.region);
}
void Display::WriteToBuffer(short x, short y, Texture const& tex) {
	// Return If Buffer Is Empty
	if (tex.buffer == nullptr)
		return;

	for (short x0 = x; x0 < tex.GetSize().X + x; ++x0)
		for (short y0 = y; y0 < tex.GetSize().Y + y; ++y0)
			if ((x0 >= 0 && y0 >= 0) && (x0 < screenSize.X && y0 < screenSize.Y))
				screenBuffer.buffer[x0 + screenSize.X * y0] = tex.buffer[(x0 - x) + tex.GetSize().X * (y0 - y)];
}
void Display::Clear() {
	memset(screenBuffer.buffer, NULL, sizeof(CHAR_INFO) * screenBuffer.size.X * screenBuffer.size.Y);
}

void Display::SetTitle(std::wstring title) {
	SetConsoleTitle(title.c_str());
}
int Display::DisplayFrequency() const {
	return displaySettings.dmDisplayFrequency;
}
COORD Display::GetSize() const {
	return screenSize;
}
HANDLE& Display::GetInputHandle() {
	return handleIn;
}
HANDLE& Display::GetOutputHandle() {
	return handleOut;
}