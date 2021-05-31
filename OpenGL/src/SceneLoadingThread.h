#pragma once
#include <thread>

class SceneLoadingThread
{
public:
	SceneLoadingThread(int sceneIndex, bool isEnabledOnLoad);
	~SceneLoadingThread() = default;

	void run();

	int getSceneIndex() const;
	bool getIsEnabledOnLoad() const;

private:
	std::thread thread;
	int sceneIndex;
	bool isEnabledOnLoad;
	bool isLoadingAssetsDone;
};
