#pragma once

/*  ############   README!!!   #############
	"GameObjectsList.h" contains all the game objects of the game!
	So all the game objects can be declared here!

	In order to create a game object, the new class must inherit GameObject class,
	which can be found in "GameObject.h".
	
	GameObject class contains 3 virtual methods:
	- "OnCreate()" : which will be called only when the game starts
	- "OnUpdate(const float deltaTime)" : which will be called every frame
	- "OnCollision(GameObject& obj, const float deltaTime)" : which will be called when the object will collide with another


	To use display or input functions, you need to include "Display.h" or "Input.h" in your file.
	To access one of their functions, type "display." or "input.".

	Other Useful Files:
	- "Pixel_Types.h"
	- "Colors.h"
*/

/*  ############   EXAMPLE   #############
#include "GameObject.h"

class Test : GameObject {

	...

	void OnCreate() {
		...
	}

	void OnUpdate(const float deltaTime) {
		...
	}

	void OnCllision(GameObject& obj, const float deltaTime) {
		...
	}

};
*/