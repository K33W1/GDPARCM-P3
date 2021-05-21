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
	assetManager.loadMeshFile("res/meshes/Bulbasaur.obj");
}

void SceneA::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* quadMesh = assetManager.getMesh("quad");
	Mesh* bulbasaurMesh = assetManager.getMesh("Bulbasaur");
	Material* bulbasaurMaterial = assetManager.getMaterial("Bulbasaur");

	// Instantiate gameobjects
	GameObject* bulbasaur = new GameObject(bulbasaurMesh, bulbasaurMaterial);
	bulbasaur->setPosition({ 0.0f, -10.0f, -50.0f });
	bulbasaur->setScale({ 5.0f, 5.0f, 5.0f });
	addGameObject(bulbasaur);
}

void SceneA::unloadAssets()
{
	// TODO: Unload assets
}
