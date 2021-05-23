#include "SceneC.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneC::SceneC()
{

}

void SceneC::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();
	assetManager.loadMeshFile("res/meshes/coin.obj");
	assetManager.loadMeshFile("res/meshes/blueShell.obj");
	assetManager.loadMeshFile("res/meshes/star.obj");
}

void SceneC::loadGameObjects()
{
	// Get assets
	AssetManager& assetManager = AssetManager::getInstance();
	Mesh* coinMesh = assetManager.getMesh("coin");
	Mesh* blueShellMesh = assetManager.getMesh("blueShell");
	Mesh* starMesh = assetManager.getMesh("star");
	Material* coinMaterial = assetManager.getMaterial("coin");
	Material* blueShellMaterial = assetManager.getMaterial("blueShell");
	Material* starMaterial = assetManager.getMaterial("star");

	// Instantiate gameobjects
	GameObject* coin = new GameObject(coinMesh, coinMaterial);
	coin->setPosition({ -20.0f, 0.0f, -50.0f });
	coin->setScale({ 0.5f, 0.5f, 0.5f });
	addGameObject(coin);
	GameObject* blueShell = new GameObject(blueShellMesh, blueShellMaterial);
	blueShell->setPosition({ 0.0f, 0.0f, -50.0f });
	blueShell->setScale({ 2.0f, 2.0f, 2.0f });
	addGameObject(blueShell);
	GameObject* star = new GameObject(starMesh, starMaterial);
	star->setPosition({ 20.0f, 0.0f, -50.0f });
	star->setScale({ 2.0f, 2.0f, 2.0f });
	addGameObject(star);
}

void SceneC::unloadAssets()
{

}