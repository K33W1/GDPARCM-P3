#include "SceneManager.h"
#include "SceneA.h"
#include "SceneB.h"
#include "SceneC.h"
#include "SceneD.h"
#include "SceneLoadingThread.h"
#include <iostream>
#include <algorithm>

void SceneManager::initialize()
{
	allScenes.push_back(new SceneA());
	allScenes.push_back(new SceneB());
	allScenes.push_back(new SceneC());
	allScenes.push_back(new SceneD());
	sceneLoadingThreads.push_back(nullptr);
	sceneLoadingThreads.push_back(nullptr);
	sceneLoadingThreads.push_back(nullptr);
	sceneLoadingThreads.push_back(nullptr);
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
	SceneLoadingThread* thread = new SceneLoadingThread(index);
	sceneLoadingThreads[index] = thread;
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

// TODO: Toggle scene
// TODO: Unload scene async

Scene* SceneManager::getScene(int index) const
{
	return allScenes[index];
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
