#pragma once
#include <Windows.h>

class Game;
class Display;

class Input {
	Display& display;

	INPUT_RECORD* buffer;
	DWORD numEvents;

	struct Key {
		bool oldState;
		bool newState;

		Key();
	};

	struct Mouse {
		static constexpr short numButtons = 2;
		COORD position;
		Key button[numButtons];

		Mouse();
	} mouse;

	struct Keyboard {
		static constexpr short numKeys = 256;
		Key keys[numKeys];

		Keyboard();
	} keyboard;

private:
	Input();
	Input(const Input&) = delete;
	~Input();

	void GetMouseInput();
	void GetKeyboardInput();
	void GetInput();

	friend class Game;
	friend class Input;

public:
	static Input& Get();

	COORD MousePosition() const;
	bool KeyPressed(const unsigned char) const;
	bool KeyReleased(const unsigned char) const;
};

