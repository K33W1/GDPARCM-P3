#include "Scene.h"
#include "GameObject.h"
#include <iostream>

void Scene::addGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::unloadGameObjects()
{
	for (const GameObject* const gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
}

const std::vector<GameObject*> Scene::getGameObjects() const
{
	return gameObjects;
}
