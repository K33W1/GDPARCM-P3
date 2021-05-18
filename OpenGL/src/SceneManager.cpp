#include "SceneManager.h"
#include "SceneA.h"
#include <algorithm>

SceneManager::SceneManager()
{
	
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::initialize()
{
	SceneA* sceneA = new SceneA();
	
	allScenes.push_back(sceneA);
}

void SceneManager::loadScene(int index)
{
	Scene* scene = allScenes[index];
	scene->load();
	loadedScenes.push_back(scene);
}

void SceneManager::unloadScene(int index)
{
	Scene* scene = allScenes[index];
	scene->unload();
	loadedScenes.erase(std::find(loadedScenes.begin(), loadedScenes.end(), scene));
}

const std::vector<const Scene*> SceneManager::getLoadedScenes() const
{
	return loadedScenes;
}
