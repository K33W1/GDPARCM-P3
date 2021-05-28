#pragma once
#include <thread>

class SceneLoadingThread
{
public:
	SceneLoadingThread(int sceneIndex);
	~SceneLoadingThread() = default;

	void run();

private:
	std::thread thread;
	int sceneIndex;
};
