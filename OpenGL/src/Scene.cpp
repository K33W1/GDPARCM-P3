#include "Scene.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "Random.h"
#include <iostream>

Scene::Scene()
	: sceneState(SceneState::Inactive), assetsLoaded(0)
{
	
}

void Scene::loadAssets()
{
	if (sceneState != SceneState::Inactive)
	{
		std::cerr << "Error: Scene is not in valid state to be loaded!\n";
		return;
	}

	sceneState = SceneState::Loading;
	
	for (const std::string& filename : assets)
	{
		AssetManager::getInstance().loadTextureFile(filename);
		assetsLoaded++;
		AssetManager::getInstance().loadMeshFile(filename);
		assetsLoaded++;
	}
}

void Scene::loadGameObjects()
{
	AssetManager& assetManager = AssetManager::getInstance();
	Shader* shader = assetManager.getShader("textured");

	for (const std::string& filename : assets)
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

	sceneState = SceneState::Active;
}

void Scene::unloadAssetsAndGameObjects()
{
	if (sceneState != SceneState::Active)
	{
		std::cerr << "Error: Scene is not in valid state to be unloaded!\n";
		return;
	}

	sceneState = SceneState::Unloading;

	for (std::string filename : assets)
	{
		AssetManager::getInstance().unloadTexture(filename);
		assetsLoaded--;
		AssetManager::getInstance().unloadMesh(filename);
		assetsLoaded--;
		AssetManager::getInstance().unloadMaterial(filename);
	}

	for (const GameObject* const gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
	
	sceneState = SceneState::Inactive;
}

ThreadSafeVector<GameObject*>& Scene::getGameObjects()
{
	return gameObjects;
}

SceneState Scene::getSceneState() const
{
	return sceneState;
}

float Scene::getPercentLoaded() const
{
	return (float)assetsLoaded / (assets.size() * 2);
}

void Scene::addAsset(const std::string& assetName)
{
	assets.push_back(assetName);
}
