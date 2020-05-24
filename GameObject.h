#pragma once
#include <string>
#include "Vector2.h"
#include "Sprite.h"

class Display;
class Input;
class GameManager;

class GameObject {
	GameManager& gameManager;
	friend class GameManager;

protected:
	Display& display;
	Input& input;

public:
	std::string name;
	Vector2 position;
	Sprite sprite;

public:
	GameObject();
	GameObject(std::string name, Vector2 position);
	virtual ~GameObject();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(const float deltaTime);
	virtual void OnCollision(GameObject& obj, const float deltaTime);
};

