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
	assetManager.loadMeshFile("res/meshes/kriss_vector.obj");
	assetManager.loadMeshFile("res/meshes/Bulbasaur.obj");
}

void SceneA::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* krissVectorMesh = assetManager.getMesh("kriss_vector");
	Mesh* bulbasaurMesh = assetManager.getMesh("Bulbasaur");
	Material* bulbasaurMaterial = assetManager.getMaterial("Bulbasaur");
	Material* krissVectorMaterial = assetManager.getMaterial("kriss_vector");

	// Instantiate gameobjects
	GameObject* bulbasaur = new GameObject(bulbasaurMesh, bulbasaurMaterial);
	bulbasaur->setPosition({ 20.0f, -10.0f, -50.0f });
	bulbasaur->setScale({ 5.0f, 5.0f, 5.0f });
	addGameObject(bulbasaur);

	GameObject* krissVector = new GameObject(krissVectorMesh, krissVectorMaterial);
	krissVector->setPosition({ -20.0f, -10.0f, -50.0f });
	krissVector->setScale({ 5.0f, 5.0f, 5.0f });
	addGameObject(krissVector);
}

void SceneA::unloadAssets()
{
	// TODO: Unload assets
}
