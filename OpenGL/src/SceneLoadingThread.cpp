#include "SceneLoadingThread.h"
#include "Scene.h"
#include "SceneManager.h"

SceneLoadingThread::SceneLoadingThread(int sceneIndex, bool isEnabledOnLoad)
	: thread(&SceneLoadingThread::run, this), sceneIndex(sceneIndex), isEnabledOnLoad(isEnabledOnLoad)
{
	thread.detach();
}

void SceneLoadingThread::run()
{
	SceneManager::getInstance().loadScene(sceneIndex, isEnabledOnLoad);

	SceneManager::getInstance().deleteSceneLoadingThread(this);
	delete this;
}

int SceneLoadingThread::getSceneIndex() const
{
	return sceneIndex;
}

bool SceneLoadingThread::getIsEnabledOnLoad() const
{
	return isEnabledOnLoad;
}
