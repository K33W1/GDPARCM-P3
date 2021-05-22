#include "SceneB.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneB::SceneB()
{
	
}

void SceneB::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();
	assetManager.loadMeshFile("res/meshes/apple.obj");
	assetManager.loadMeshFile("res/meshes/coca_cola.obj");
	assetManager.loadMeshFile("res/meshes/ham.obj");
}

void SceneB::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* appleMesh = assetManager.getMesh("apple");
	Mesh* cocaColaMesh = assetManager.getMesh("coca_cola");
	Mesh* meshHam = assetManager.getMesh("ham");
	Material* appleMaterial = assetManager.getMaterial("apple");
	Material* cocaColaMaterial = assetManager.getMaterial("coca_cola");
	Material* meshMaterial = assetManager.getMaterial("ham");

	// Instantiate gameobjects
	GameObject* apple = new GameObject(appleMesh, appleMaterial);
	apple->setPosition({ -20.0f, 0.0f, -50.0f });
	apple->setScale({ 3.0f, 3.0f, 3.0f });
	addGameObject(apple);
	GameObject* cocaCola = new GameObject(cocaColaMesh, cocaColaMaterial);
	cocaCola->setPosition({ 0.0f, 0.0f, -50.0f });
	cocaCola->setScale({ 3.0f, 3.0f, 3.0f });
	addGameObject(cocaCola);
	GameObject* ham = new GameObject(meshHam, meshMaterial);
	ham->setPosition({ 20.0f, 0.0f, -50.0f });
	ham->setScale({ 3.0f, 3.0f, 3.0f });
	addGameObject(ham);
}

void SceneB::unloadAssets()
{
	
}
