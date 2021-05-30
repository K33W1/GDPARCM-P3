#pragma once
#include <thread>

class SceneUnloadingThread
{
public:
	SceneUnloadingThread(int sceneIndex);
	~SceneUnloadingThread() = default;

	void run();

	int getSceneIndex() const;

private:
	std::thread thread;
	int sceneIndex;
};
