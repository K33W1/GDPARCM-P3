#include "SceneLoadingThread.h"
#include "SceneManager.h"

SceneLoadingThread::SceneLoadingThread(int sceneIndex)
	: thread(&SceneLoadingThread::run, this), sceneIndex(sceneIndex)
{
	thread.detach();
}

void SceneLoadingThread::run()
{
	SceneManager::getInstance().loadScene(sceneIndex);
}
