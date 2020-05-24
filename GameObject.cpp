#include "GameObject.h"
#include "Display.h"
#include "Input.h"
#include "GameManager.h"

GameObject::GameObject() : display(Display::Get()), input(Input::Get()), gameManager(GameManager::Get()) {
	name = "Default";
	position = Vector2(0, 0);

	gameManager.AddGameObject(this);
}
GameObject::GameObject(std::string name, Vector2 position) : display(Display::Get()), input(Input::Get()), gameManager(GameManager::Get()) {
	this->name = name;
	this->position = position;

	gameManager.AddGameObject(this);
}
GameObject::~GameObject() {
	gameManager.RemoveGameObject(this);
}

void GameObject::OnCreate() {}
void GameObject::OnUpdate(const float deltaTime) {}
void GameObject::OnCollision(GameObject& obj, const float deltaTime) {}