#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "GameManager.h"
#include <chrono>

Game::Game() : display(Display::Get()), input(Input::Get()), gameManager(GameManager::Get()) {
	name = L"Default";
	
	frameLimit = 1 / (float)display.DisplayFrequency();
	vsync = false;
	running = false;
}

Game::Game(std::wstring name, short screenWidth, short screenHeight, short fontWidth, short fontHeight)
	: display(Display::Get()), input(Input::Get()), gameManager(GameManager::Get())
{
	this->name = name;

	frameLimit = 1 / (float)display.DisplayFrequency();
	vsync = false;
	running = false;

	// Init Display
	display.Init(name, screenWidth, screenHeight, fontWidth, fontHeight);
}


void Game::Start() {
	running = true;
	Run();
}
void Game::Run() {

	// Frame Duration
	float deltaTime = 0;

	// Create Game Objects
	gameManager.CreateGameObjects();

	// Start Game Loop
	while (running) {
		// Start Frame Timer
		auto startFrameTime = std::chrono::high_resolution_clock::now();

		// Get Input
		input.GetInput();

		// Update Game Objects
		gameManager.UpdateGameObjects(deltaTime);

		// Check for Collided Objects
		gameManager.CollidedGameObjects(deltaTime);

		// Draw Game Objects
		gameManager.DrawGameObjects();

		// Update Title
		std::wstring title;
		int fps = (int)round(1 / deltaTime);
		title = name + L" - FPS: " + std::to_wstring(fps);
		display.SetTitle(title);

		// Draw Buffer to Screen & Clear Screen
		display.DrawBuffer();
		display.Clear();

		// Stop Frame Timer
		auto endFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> frameTime = endFrameTime - startFrameTime;
		deltaTime = frameTime.count();
		
		// Limit FPS
		if (vsync)
			if (deltaTime < frameLimit) {
				Sleep((DWORD)((frameLimit - deltaTime) * 1000));
				deltaTime = frameLimit;
			}
	}
}
void Game::Close() {
	running = false;
}

void Game::EnableVSync() {
	vsync = true;
}