#include "GameManager.h"
#include "Display.h"
#include "GameObject.h"

GameManager::GameManager() {}
GameManager& GameManager::Get() {
	static GameManager gameManager;
	return gameManager;
}

void GameManager::AddGameObject(GameObject* const gameObject) {
	gameObjectList.push_back(gameObject);
}
void GameManager::RemoveGameObject(GameObject* const gameObject) {
	gameObjectList.remove(gameObject);
}

void GameManager::CreateGameObjects() const {
	for (GameObject* obj : gameObjectList)
		obj->OnCreate();
}
void GameManager::UpdateGameObjects(const float deltaTime) const {
	for (GameObject* obj : gameObjectList) 
		obj->OnUpdate(deltaTime);
}
void GameManager::CollidedGameObjects(const float deltaTime) const {
	for (auto obj0 = gameObjectList.begin(); obj0 != gameObjectList.end(); ++obj0)
		for (auto obj1 = std::next(obj0); obj1 != gameObjectList.end(); ++obj1) {
			// Get Corners of Game Objects
			COORD objVertices0[4] = {
				{ (short)(*obj0)->position.x, (short)(*obj0)->position.y },
				{ ((short)(*obj0)->position.x + (*obj0)->sprite.texture.size.X - 1), (short)(*obj0)->position.y },
				{ (short)(*obj0)->position.x, ((short)(*obj0)->position.y + (*obj0)->sprite.texture.size.Y - 1) },
				{ ((short)(*obj0)->position.x + (*obj0)->sprite.texture.size.X - 1), ((short)(*obj0)->position.y + (*obj0)->sprite.texture.size.Y - 1) }
			};
			COORD objVertices1[4] = {
				{ (short)(*obj1)->position.x, (short)(*obj1)->position.y },
				{ ((short)(*obj1)->position.x + (*obj1)->sprite.texture.size.X - 1), (short)(*obj1)->position.y },
				{ (short)(*obj1)->position.x, ((short)(*obj1)->position.y + (*obj1)->sprite.texture.size.Y - 1) },
				{ ((short)(*obj1)->position.x + (*obj1)->sprite.texture.size.X - 1), ((short)(*obj1)->position.y + (*obj1)->sprite.texture.size.Y - 1) }
			};

			// Check If One Corner Is Inside of The Other Object
			for (short vertex = 0; vertex < 4; ++vertex)
				if ((objVertices1[vertex].X >= objVertices0[0].X && objVertices1[vertex].X <= objVertices0[3].X) &&
					(objVertices1[vertex].Y >= objVertices0[0].Y && objVertices1[vertex].Y <= objVertices0[3].Y))
				{
					(*obj0)->OnCollision(**obj1, deltaTime);
					(*obj1)->OnCollision(**obj0, deltaTime);
				}
		}
}
void GameManager::DrawGameObjects() const {
	for (GameObject* obj : gameObjectList)
		Display::Get().WriteToBuffer((short)obj->position.x, (short)obj->position.y, obj->sprite.texture);
}