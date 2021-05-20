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
	Mesh* teapotMesh = assetManager.getMesh("teapot");
	Mesh* bulbasaurMesh = assetManager.getMesh("bulbasaur");
	Shader* basicShader = assetManager.getShader("basic");

	// Instantiate gameobjects
	GameObject* teapot = new GameObject(teapotMesh, basicShader);
	teapot->setPosition({ 0.0f, 0.0f, -500.0f });
	addGameObject(teapot);
	GameObject* bulbasaur = new GameObject(bulbasaurMesh, basicShader);
	bulbasaur->setPosition({ 0.0f, 0.0f, -100.0f });
	bulbasaur->setScale({ 5.0f, 5.0f, 5.0f });
	addGameObject(bulbasaur);
}

void SceneA::unloadAssets()
{
	// TODO: Unload assets
}
