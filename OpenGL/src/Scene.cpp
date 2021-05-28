#include "Scene.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "Random.h"

void Scene::loadAssets()
{
	AssetManager& assetManager = AssetManager::getInstance();

	for (std::string filename : assets)
	{
		assetManager.loadTextureFile(filename);
		assetsLoaded++;
		assetManager.loadMeshFile(filename);
		assetsLoaded++;
	}
}

void Scene::loadGameObjects()
{
	AssetManager& assetManager = AssetManager::getInstance();
	Shader* shader = assetManager.getShader("textured");

	for (std::string filename : assets)
	{
		Texture* texture = assetManager.getTexture(filename);
		assetManager.createMaterial(filename, shader, texture, glm::vec4(1.0f));

		Mesh* mesh = assetManager.getMesh(filename);
		Material* material = assetManager.getMaterial(filename);

		GameObject* go = new GameObject(mesh, material);
		float posX = Random::getRandom(-25.0f, 25.0f);
		float posY = Random::getRandom(-50.0f, 25.0f);
		float posZ = Random::getRandom(-150.0f, -50.0f);
		go->setPosition({ posX, posY, posZ });
		go->setScale({ 5.0f, 5.0f, 5.0f });
		gameObjects.push_back(go);
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
	assetsLoaded = 0;
}

void Scene::manualSharedLockGameObjects()
{
	gameObjects.manualSharedLock();
}

void Scene::manualSharedUnlockGameObjects()
{
	gameObjects.manualSharedUnlock();
}

ThreadSafeVector<GameObject*>& Scene::getGameObjects()
{
	return gameObjects;
}

bool Scene::isLoaded()
{
	return gameObjects.size() == assets.size();
}

float Scene::getPercentLoaded()
{
	return (float)assetsLoaded / (assets.size() * 2);
}

void Scene::addAsset(const std::string& assetName)
{
	assets.push_back(assetName);
}
