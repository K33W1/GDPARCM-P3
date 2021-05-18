#include "SceneA.h"
#include "AssetManager.h"
#include "GameObject.h"

SceneA::SceneA()
{
	
}

void SceneA::load()
{
	AssetManager& assetManager = AssetManager::getInstance();

	const Mesh* teapot = assetManager.getMesh("teapot");
	Shader* basicShader = assetManager.getShader("basic");
	
	GameObject* teapotGO = new GameObject(teapot, basicShader);
	
	teapotGO->setPosition({ 0.0f, 0.0f, -250.0f });

	addGameObject(teapotGO);
}
