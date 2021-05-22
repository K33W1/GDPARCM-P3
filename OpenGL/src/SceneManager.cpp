#include "SceneManager.h"
#include "SceneA.h"
#include "SceneB.h"
#include <iostream>
#include <algorithm>
#include <thread>

void SceneManager::initialize()
{
	allScenes.push_back(new SceneA());
	allScenes.push_back(new SceneB());
}

void SceneManager::loadScene(int index)
{
	Scene* scene = allScenes[index];
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);
	
	if (sceneItr != activeScenes.end())
	{
		std::cout << "Tried to load an already loaded scene!";
		return;
	}
	
	scene->loadAssets();
	
	newLoadedScenes.push_back(scene);
}

void SceneManager::loadSceneAsync(int index)
{
	std::thread* thread = new std::thread(&SceneManager::loadScene, this, index);
	loadingSceneThreads.push_back(thread);
	thread->detach();
}

void SceneManager::unloadScene(int index)
{
	Scene* scene = allScenes[index];
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);
	
	if (sceneItr == activeScenes.end())
	{
		std::cout << "Tried to unload an already unloaded scene!";
		return;
	}

	activeScenes.erase(sceneItr);
	
	scene->unloadGameObjects();
	scene->unloadAssets();
}

void SceneManager::instantiateNewLoadedScenes()
{
	for (Scene* scene : newLoadedScenes)
	{
		scene->loadGameObjects();
		activeScenes.push_back(scene);
	}

	newLoadedScenes.clear();
}

const std::vector<Scene*>& SceneManager::getActiveScenes()
{
	return activeScenes;
}
