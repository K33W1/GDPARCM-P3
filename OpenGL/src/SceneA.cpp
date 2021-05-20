#include "SceneA.h"
#include "AssetManager.h"
#include "GameObject.h"
#include <thread>
#include <chrono>

SceneA::SceneA()
{
	
}

void SceneA::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();
	assetManager.loadMeshFile("res/meshes/teapot.obj");
	assetManager.loadMeshFile("res/meshes/bulbasaur.obj");
}

void SceneA::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* quadMesh = assetManager.getMesh("quad");
	Mesh* bulbasaurMesh = assetManager.getMesh("bulbasaur");
	Material* bulbasaurMaterial = assetManager.getMaterial("bulbasaur");

	// Instantiate gameobjects
	GameObject* quad = new GameObject(quadMesh, bulbasaurMaterial);
	quad->setPosition({ 0.0f, 0.0f, -500.0f });
	addGameObject(quad);
	GameObject* bulbasaur = new GameObject(bulbasaurMesh, bulbasaurMaterial);
	bulbasaur->setPosition({ 0.0f, 0.0f, -100.0f });
	bulbasaur->setScale({ 5.0f, 5.0f, 5.0f });
	addGameObject(bulbasaur);
}

void SceneA::unloadAssets()
{
	// TODO: Unload assets
}
