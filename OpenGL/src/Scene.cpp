#include "Scene.h"
#include "AssetManager.h"
#include "GameObject.h"
#include <iostream>

void Scene::addGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();

	// Get shader
	Shader* shader = assetManager.getShader("textured");

	for (std::string filename : assets)
	{
		assetManager.loadTextureFile(filename);
		assetManager.loadMeshFile(filename);
	}
}

void Scene::loadGameObjects()
{
	AssetManager& assetManager = AssetManager::getInstance();

	Shader* shader = assetManager.getShader("textured");

	for (std::string filename : assets) {
		Texture* texture = assetManager.getTexture(filename);
		assetManager.createMaterial(filename, shader, texture, glm::vec4(1.0f));

		Mesh* mesh = assetManager.getMesh(filename);
		Material* material = assetManager.getMaterial(filename);

		GameObject* go = new GameObject(mesh, material);
		go->setPosition({ 0.0f, 0.0f, -50.0f });
		go->setScale({ 5.0f, 5.0f, 5.0f });
		addGameObject(go);
	}
}

void Scene::unloadGameObjects()
{
	for (const GameObject* const gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
}

void Scene::unloadAssets()
{
	
}

const std::vector<GameObject*> Scene::getGameObjects() const
{
	return gameObjects;
}