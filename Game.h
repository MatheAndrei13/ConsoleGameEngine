#pragma once
#include <string>

class Display;
class Input;
class GameManager;

class Game {
	std::wstring name;
	Display& display;
	Input& input;
	GameManager& gameManager;

	float frameLimit;
	bool vsync;
	bool running;

public:
	Game();
	Game(std::wstring name, short screenWidth, short screenHeight, short fontWidth, short fontHeight);

	void Start();
	void Close();

	void EnableVSync();

private:
	void Run();
};

