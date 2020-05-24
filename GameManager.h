#pragma once
#include <list>

class GameObject;

class GameManager {
	std::list<GameObject*> gameObjectList;

private:
	GameManager();
	GameManager(const GameManager&) = delete;

public:
	static GameManager& Get();

	void AddGameObject(GameObject* const);
	void RemoveGameObject(GameObject* const);
	void CreateGameObjects() const;
	void UpdateGameObjects(const float deltaTime) const;
	void CollidedGameObjects(const float deltaTime) const;
	void DrawGameObjects() const;
};

