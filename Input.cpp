#include "Input.h"
#include "Display.h"
#include <thread>

Input::Input() : display(Display::Get()) {
	buffer = nullptr;
	numEvents = 0;
}
Input::~Input() {
	if (buffer != nullptr)
		delete[] buffer;
}
Input& Input::Get() {
	static Input input;
	return input;
}

Input::Key::Key() {
	oldState = false;
	newState = false;
}
Input::Mouse::Mouse() {
	position = { 0, 0 };
}
Input::Keyboard::Keyboard() {}

void Input::GetInput() {
	// Get Input Handle from Display
	static HANDLE handleIn = display.GetInputHandle();

	// Get Number of Console Input Events
	GetNumberOfConsoleInputEvents(handleIn, &numEvents);

	// Return If 0 Events
	if (!numEvents)
		return;

	// Read Console Input
	buffer = new INPUT_RECORD[numEvents];
	ReadConsoleInput(handleIn, buffer, numEvents, &numEvents);

	// Check Mouse & Keyboard Inputs (different threads)
	std::thread mouseThread(&Input::GetMouseInput, this);
	std::thread keyboardThread(&Input::GetKeyboardInput, this);

	// Wait for Threads
	mouseThread.join();
	keyboardThread.join();

	// Reset Buffer & numEvents
	numEvents = 0;
	delete[] buffer;
}
void Input::GetMouseInput() {
	// Update Old Button State
	for (short i = 0; i < mouse.numButtons; ++i)
		mouse.button[i].oldState = mouse.button[i].newState;

	// Check for Mouse Events
	for (DWORD i = 0; i < numEvents; ++i) {
		switch (buffer[i].EventType) {
		case MOUSE_EVENT:
			// Update Mouse Position
			if (buffer[i].Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
				mouse.position = buffer[i].Event.MouseEvent.dwMousePosition;
			// Update New Button State
			mouse.button[0].newState = (buffer[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED);
			mouse.button[1].newState = (buffer[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED);
			break;
		}
	}
}
void Input::GetKeyboardInput() {
	// Loop Through Keys
	for (short i = 0; i < keyboard.numKeys; ++i) {
		// Update Old Key State
		keyboard.keys[i].oldState = keyboard.keys[i].newState;
		// Update New Key State
		keyboard.keys[i].newState = GetAsyncKeyState(i) & 0x8000;
	}
}

COORD Input::MousePosition() const {
	return COORD{ mouse.position.X, mouse.position.Y };
}
bool Input::KeyPressed(const unsigned char VirtualKeyCode) const {
	if (VirtualKeyCode == VK_LBUTTON || VirtualKeyCode == VK_RBUTTON)
		return mouse.button[VirtualKeyCode-1].newState;
	return keyboard.keys[VirtualKeyCode].newState;
}
bool Input::KeyReleased(const unsigned char VirtualKeyCode) const {
	if (VirtualKeyCode == VK_LBUTTON || VirtualKeyCode == VK_RBUTTON)
		return mouse.button[VirtualKeyCode-1].oldState && !mouse.button[VirtualKeyCode-1].newState;
	return keyboard.keys[VirtualKeyCode].oldState && !keyboard.keys[VirtualKeyCode].newState;
}