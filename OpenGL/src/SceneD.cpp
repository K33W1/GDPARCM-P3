#include "SceneD.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneD::SceneD()
{
	assets.push_back("ancientPick");
	assets.push_back("bow");
	assets.push_back("superHammer");
}

/*
void SceneD::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();

	for (std::string filename : assets) {
		assetManager.loadTextureFile(filename);
		assetManager.loadMeshFile(filename);
	}

	// assetManager.loadMeshFile("res/meshes/ancientPick.obj");
	// assetManager.loadMeshFile("res/meshes/bow.obj");
	// assetManager.loadMeshFile("res/meshes/superHammer.obj");
}

void SceneD::loadGameObjects()
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

	// Get assets
	//AssetManager& assetManager = AssetManager::getInstance();
	//Mesh* ancientPickMesh = assetManager.getMesh("ancientPick");
	//Mesh* bowMesh = assetManager.getMesh("bow");
	//Mesh* superHammerMesh = assetManager.getMesh("superHammer");
	//Material* ancientPickMaterial = assetManager.getMaterial("ancientPick");
	//Material* bowMaterial = assetManager.getMaterial("bow");
	//Material* superHammerMaterial = assetManager.getMaterial("superHammer");

	//// Instantiate gameobjects
	//GameObject* ancientPick = new GameObject(ancientPickMesh, ancientPickMaterial);
	//ancientPick->setPosition({ -20.0f, 0.0f, -50.0f });
	//ancientPick->setRotation({ 0.0f, 0.0f, 90.0f });
	//ancientPick->setScale({ 2.0f, 2.0f, 2.0f });
	//addGameObject(ancientPick);
	//GameObject* bow = new GameObject(bowMesh, bowMaterial);
	//bow->setPosition({ 0.0f, 0.0f, -50.0f });
	//bow->setScale({ 10.0f, 10.0f, 10.0f });
	//addGameObject(bow);
	//GameObject* superHammer = new GameObject(superHammerMesh, superHammerMaterial);
	//superHammer->setPosition({ 20.0f, 0.0f, -50.0f });
	//superHammer->setRotation({ 0.0f, 0.0f, 90.0f });
	//superHammer->setScale({ 2.0f, 2.0f, 2.0f });
	//addGameObject(superHammer);
}

void SceneD::unloadAssets()
{

}
*/