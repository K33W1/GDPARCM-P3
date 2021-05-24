#include "SceneA.h"
#include "AssetManager.h"
#include "GameObject.h"
#include <thread>
#include <chrono>

#include <iostream>

SceneA::SceneA()
{
	assets.push_back("kriss_vector");
	assets.push_back("bulbasaur");
}

/*
void SceneA::loadAssets()
{
	// Load assets
	AssetManager& assetManager = AssetManager::getInstance();

	// Get shader
	Shader* shader = assetManager.getShader("textured");

	for (std::string filename : assets) {
		assetManager.loadTextureFile(filename);
		assetManager.loadMeshFile(filename);
	}

	//assetManager.loadMeshFile("res/meshes/kriss_vector.obj");
	//assetManager.loadMeshFile("res/meshes/bulbasaur.obj");
}

void SceneA::loadGameObjects()
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

	//Texture* bulbasaurTexture = assetManager.getTexture("bulbasaur");
	//assetManager.createMaterial("bulbasaur", shader, bulbasaurTexture, glm::vec4(1.0f));
	//Texture* krissVectorTexture = assetManager.getTexture("kriss_vector");
	//assetManager.createMaterial("kriss_vector", shader, krissVectorTexture, glm::vec4(1.0f));

	// Get assets
	//Mesh* krissVectorMesh = assetManager.getMesh("kriss_vector");
	//Mesh* bulbasaurMesh = assetManager.getMesh("bulbasaur");
	//Material* bulbasaurMaterial = assetManager.getMaterial("bulbasaur");
	//Material* krissVectorMaterial = assetManager.getMaterial("kriss_vector");

	////// Instantiate gameobjects
	//GameObject* bulbasaur = new GameObject(bulbasaurMesh, bulbasaurMaterial);
	//bulbasaur->setPosition({ 20.0f, -10.0f, -50.0f });
	//bulbasaur->setScale({ 5.0f, 5.0f, 5.0f });
	//addGameObject(bulbasaur);

	//GameObject* krissVector = new GameObject(krissVectorMesh, krissVectorMaterial);
	//krissVector->setPosition({ -20.0f, -10.0f, -50.0f });
	//krissVector->setScale({ 5.0f, 5.0f, 5.0f });
	//addGameObject(krissVector);
}

void SceneA::unloadAssets()
{
	// TODO: Unload assets
}
*/