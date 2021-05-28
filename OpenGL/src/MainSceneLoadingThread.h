#pragma once
#include <thread>

class MainSceneLoadingThread
{
public:
	MainSceneLoadingThread(int sceneIndex);
	~MainSceneLoadingThread() = default;

	void run();

private:
	std::thread thread;
	int sceneIndex;
};
