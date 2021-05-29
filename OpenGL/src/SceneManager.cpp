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
}

void SceneManager::loadScene(int index, bool loadAsEnabled)
{
	Scene* scene = allScenes[index];
	auto enabledSceneItr = std::find(enabledScenes.begin(), enabledScenes.end(), scene);
	auto disabledSceneItr = std::find(disabledScenes.begin(), disabledScenes.end(), scene);
	
	if (enabledSceneItr != enabledScenes.end() || disabledSceneItr != disabledScenes.end())
	{
		std::cerr << "Tried to load an already loaded scene!\n";
		return;
	}

	loadScene(scene, loadAsEnabled);
}

void SceneManager::loadScene(Scene* scene, bool loadAsEnabled)
{
	scene->loadAssets();

	if (loadAsEnabled)
	{
		newLoadedScenesAsEnabled.push_back(scene);
	}
	else
	{
		newLoadedScenesAsDisabled.push_back(scene);
	}
}

void SceneManager::loadSceneAsync(int index, bool loadAsEnabled)
{
	sceneLoadingThreads.push_back(new SceneLoadingThread(index, loadAsEnabled));
}

void SceneManager::loadAllScenesAsync(bool loadAsEnabled)
{
	for (int i = 0; i < allScenes.size(); i++)
	{
		Scene* scene = allScenes[i];
		SceneState sceneState = scene->getSceneState();
		
		if (sceneState == SceneState::Unloaded)
		{
			sceneLoadingThreads.push_back(new SceneLoadingThread(i, loadAsEnabled));
		}
		else if (sceneState == SceneState::Disabled)
		{
			enableScene(scene);
		}
	}
}

void SceneManager::unloadScene(int index)
{
	Scene* scene = allScenes[index];
	auto disabledSceneItr = std::find(disabledScenes.begin(), disabledScenes.end(), scene);
	auto enabledSceneItr = std::find(enabledScenes.begin(), enabledScenes.end(), scene);

	if (disabledSceneItr != disabledScenes.end())
	{
		disabledScenes.erase(disabledSceneItr);
	}
	else if (enabledSceneItr != enabledScenes.end())
	{
		enabledScenes.erase(enabledSceneItr);
	}
	else
	{
		std::cerr << "Error: Tried to unload a scene in an invalid state!\n";
		return;
	}
	
	scene->unloadAssetsAndGameObjects();
}

void SceneManager::unloadSceneAsync(int index)
{
	// TODO: Make it async
	unloadScene(index);
}

void SceneManager::switchToScene(int index)
{
	Scene* nextScene = allScenes[index];
	
	// Disable current scene if scene to switch to is the current one
	if (enabledScenes.size() == 1 && enabledScenes[0] == nextScene) 
	{
		disableScene(nextScene);
		return;
	}

	// Disable all Scenes
	std::vector<Scene*> enabledScenesCopy = enabledScenes;
	for (Scene* const scene : enabledScenesCopy)
	{
		disableScene(scene);
	}

	SceneState sceneState = nextScene->getSceneState();
	if (sceneState == SceneState::Unloaded)
	{
		loadSceneAsync(index, true);
	}
	else if (sceneState == SceneState::Disabled)
	{
		enableScene(nextScene);
	}
	else if (sceneState == SceneState::Enabled)
	{
		disableScene(nextScene);
	}
}

void SceneManager::instantiateNewLoadedScenes()
{
	for (Scene* scene : newLoadedScenesAsEnabled)
	{
		scene->loadGameObjects();
		scene->enable();
		enabledScenes.push_back(scene);
	}
	
	for (Scene* scene : newLoadedScenesAsDisabled)
	{
		scene->loadGameObjects();
		scene->disable();
		disabledScenes.push_back(scene);
	}

	newLoadedScenesAsEnabled.clear();
	newLoadedScenesAsDisabled.clear();
}

Scene* SceneManager::getScene(int index) const
{
	return allScenes[index];
}

Scene* SceneManager::getMainLoadingScene()
{
	if (sceneLoadingThreads.size() >= 1)
	{
		// Just get the first scene
		SceneLoadingThread* sceneLoadingThread = sceneLoadingThreads[0];
		
		if (sceneLoadingThread->getIsEnabledOnLoad())
		{
			return allScenes[sceneLoadingThread->getSceneIndex()];
		}
	}

	return nullptr;
}

const std::vector<Scene*>& SceneManager::getEnabledScenes() const
{
	return enabledScenes;
}

void SceneManager::deleteSceneLoadingThread(SceneLoadingThread* thread)
{
	sceneLoadingThreads.remove(thread);
}

void SceneManager::enableScene(Scene* scene)
{
	disabledScenes.erase(std::find(disabledScenes.begin(), disabledScenes.end(), scene));
	enabledScenes.push_back(scene);
	scene->enable();
}

void SceneManager::disableScene(Scene* scene)
{
	enabledScenes.erase(std::find(enabledScenes.begin(), enabledScenes.end(), scene));
	disabledScenes.push_back(scene);
	scene->disable();
}
