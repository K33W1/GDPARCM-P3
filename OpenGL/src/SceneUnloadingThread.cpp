#include "SceneUnloadingThread.h"
#include "SceneManager.h"

SceneUnloadingThread::SceneUnloadingThread(int sceneIndex)
	: thread(&SceneUnloadingThread::run, this), sceneIndex(sceneIndex)
{
	thread.detach();
}

void SceneUnloadingThread::run()
{
	SceneManager::getInstance().unloadScene(sceneIndex);
	SceneManager::getInstance().deleteSceneUnloadingThread(this);
	delete this;
}

int SceneUnloadingThread::getSceneIndex() const
{
	return sceneIndex;
}
