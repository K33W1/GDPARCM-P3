#include "SceneC.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneC::SceneC()
{
	assets.push_back("coin");
	assets.push_back("blueShell");
	assets.push_back("star");
}

/*
void SceneC::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();

	// Get shader
	Shader* shader = assetManager.getShader("textured");

	for (std::string filename : assets) {
		assetManager.loadTextureFile(filename);
		assetManager.loadMeshFile(filename);
	}

	// assetManager.loadMeshFile("res/meshes/coin.obj");
	// assetManager.loadMeshFile("res/meshes/blueShell.obj");
	// assetManager.loadMeshFile("res/meshes/star.obj");
}

void SceneC::loadGameObjects()
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
	//Mesh* coinMesh = assetManager.getMesh("coin");
	//Mesh* blueShellMesh = assetManager.getMesh("blueShell");
	//Mesh* starMesh = assetManager.getMesh("star");
	//Material* coinMaterial = assetManager.getMaterial("coin");
	//Material* blueShellMaterial = assetManager.getMaterial("blueShell");
	//Material* starMaterial = assetManager.getMaterial("star");

	//// Instantiate gameobjects
	//GameObject* coin = new GameObject(coinMesh, coinMaterial);
	//coin->setPosition({ -20.0f, 0.0f, -50.0f });
	//coin->setScale({ 0.5f, 0.5f, 0.5f });
	//addGameObject(coin);
	//GameObject* blueShell = new GameObject(blueShellMesh, blueShellMaterial);
	//blueShell->setPosition({ 0.0f, 0.0f, -50.0f });
	//blueShell->setScale({ 2.0f, 2.0f, 2.0f });
	//addGameObject(blueShell);
	//GameObject* star = new GameObject(starMesh, starMaterial);
	//star->setPosition({ 20.0f, 0.0f, -50.0f });
	//star->setScale({ 2.0f, 2.0f, 2.0f });
	//addGameObject(star);
}

void SceneC::unloadAssets()
{

}
*/