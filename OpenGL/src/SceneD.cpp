#include "SceneD.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneD::SceneD()
{

}

void SceneD::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();
	assetManager.loadMeshFile("res/meshes/ancientPick.obj");
	assetManager.loadMeshFile("res/meshes/bow.obj");
	assetManager.loadMeshFile("res/meshes/superHammer.obj");
}

void SceneD::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* ancientPickMesh = assetManager.getMesh("ancientPick");
	Mesh* bowMesh = assetManager.getMesh("bow");
	Mesh* superHammerMesh = assetManager.getMesh("superHammer");
	Material* ancientPickMaterial = assetManager.getMaterial("ancientPick");
	Material* bowMaterial = assetManager.getMaterial("bow");
	Material* superHammerMaterial = assetManager.getMaterial("superHammer");

	// Instantiate gameobjects
	GameObject* ancientPick = new GameObject(ancientPickMesh, ancientPickMaterial);
	ancientPick->setPosition({ -20.0f, 0.0f, -50.0f });
	ancientPick->setRotation({ 0.0f, 0.0f, 90.0f });
	ancientPick->setScale({ 2.0f, 2.0f, 2.0f });
	addGameObject(ancientPick);
	GameObject* bow = new GameObject(bowMesh, bowMaterial);
	bow->setPosition({ 0.0f, 0.0f, -50.0f });
	bow->setScale({ 10.0f, 10.0f, 10.0f });
	addGameObject(bow);
	GameObject* superHammer = new GameObject(superHammerMesh, superHammerMaterial);
	superHammer->setPosition({ 20.0f, 0.0f, -50.0f });
	superHammer->setRotation({ 0.0f, 0.0f, 90.0f });
	superHammer->setScale({ 2.0f, 2.0f, 2.0f });
	addGameObject(superHammer);
}

void SceneD::unloadAssets()
{

}