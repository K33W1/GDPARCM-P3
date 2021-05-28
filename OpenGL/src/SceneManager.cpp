#include "SceneManager.h"
#include "SceneA.h"
#include "SceneB.h"
#include "SceneC.h"
#include "SceneD.h"
#include "SceneLoadingThread.h"
#include "MainSceneLoadingThread.h"
#include <iostream>
#include <algorithm>

void SceneManager::initialize()
{
	allScenes.push_back(new SceneA());
	allScenes.push_back(new SceneB());
	allScenes.push_back(new SceneC());
	allScenes.push_back(new SceneD());
}

void SceneManager::loadSceneAsMain(int index)
{
	Scene* scene = allScenes[index];
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);

	if (sceneItr != activeScenes.end())
	{
		std::cout << "Tried to load an already loaded scene!\n";
		return;
	}

	mainLoadingScene = scene;
	loadScene(scene);
}

void SceneManager::loadScene(int index)
{
	Scene* scene = allScenes[index];
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);
	
	if (sceneItr != activeScenes.end())
	{
		std::cout << "Tried to load an already loaded scene!\n";
		return;
	}

	loadScene(scene);
}

void SceneManager::loadScene(Scene* scene)
{
	scene->loadAssets();
	newLoadedScenes.push_back(scene);
}

void SceneManager::loadSceneAsync(int index)
{
	new SceneLoadingThread(index);
}

void SceneManager::loadSceneAsMainAsync(int index)
{
	new MainSceneLoadingThread(index);
}

void SceneManager::loadAllScenesAsync()
{
	for (int i = 0; i < allScenes.size(); i++)
	{
		if (allScenes[i]->getSceneState() == SceneState::Inactive)
		{
			new SceneLoadingThread(i);
		}
	}
}

void SceneManager::unloadScene(int index)
{
	Scene* scene = allScenes[index];
	auto sceneItr = std::find(activeScenes.begin(), activeScenes.end(), scene);
	
	if (sceneItr == activeScenes.end())
	{
		std::cout << "Tried to unload an already unloaded scene!\n";
		return;
	}

	activeScenes.erase(sceneItr);
	
	scene->unloadAssetsAndGameObjects();
}

void SceneManager::unloadSceneAsync(int index)
{
	// TODO: Make it async
	unloadScene(index);
}

void SceneManager::toggleScene(int index)
{
	SceneState sceneState = allScenes[index]->getSceneState();
	
	if (sceneState == SceneState::Inactive)
	{
		loadSceneAsMainAsync(index);
	}
	else if (sceneState == SceneState::Active)
	{
		unloadSceneAsync(index);
	}
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

Scene* SceneManager::getScene(int index) const
{
	return allScenes[index];
}

Scene* SceneManager::getMainScene() const
{
	return mainLoadingScene;
}

const std::vector<Scene*>& SceneManager::getActiveScenes()
{
	return activeScenes;
}
