#include "SceneManager.h"
#include "SceneA.h"
#include <iostream>
#include <algorithm>
#include <thread>

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
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);
	
	if (sceneItr != activeScenes.end())
	{
		std::cout << "Tried to load an already loaded scene!";
		return;
	}
	
	newlyLoadedScenes.push_back(scene);
	scene->load();
}

void SceneManager::loadSceneAsync(int index)
{
	std::thread* thread = new std::thread(&SceneManager::loadSceneAsyncImpl, this, index);
	loadingSceneThreads.push_back(thread);
	thread->detach();
}

void SceneManager::loadSceneAsyncImpl(int index)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	loadScene(index);
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
	
	scene->unload();
}

void SceneManager::startNewlyLoadedScenes()
{
	for (int i = 0; i < newlyLoadedScenes.size(); i++)
	{
		activeScenes.push_back(newlyLoadedScenes[i]);
	}

	newlyLoadedScenes.clear();
}

const std::vector<const Scene*> SceneManager::getActiveScenes() const
{
	return activeScenes;
}
