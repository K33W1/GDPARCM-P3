#include "MainSceneLoadingThread.h"
#include "SceneManager.h"

MainSceneLoadingThread::MainSceneLoadingThread(int sceneIndex)
	: thread(&MainSceneLoadingThread::run, this), sceneIndex(sceneIndex)
{
	thread.detach();
}

void MainSceneLoadingThread::run()
{
	SceneManager::getInstance().loadSceneAsMain(sceneIndex);
	delete this;
}
