#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	unload();
}

void Scene::addGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::unload()
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
