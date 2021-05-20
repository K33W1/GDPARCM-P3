#pragma once
#include "Singleton.h"
#include "ThreadSafeVector.h"
#include <vector>
#include <thread>

class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	void initialize();

	void instantiateNewLoadedScenes();

	void loadScene(int index);
	void loadSceneAsync(int index);
	void unloadScene(int index);

	const std::vector<Scene*>& getActiveScenes();

private:
	SceneManager() = default;
	~SceneManager() override = default;

	ThreadSafeVector<std::thread*> loadingSceneThreads;
	ThreadSafeVector<Scene*> newLoadedScenes;
	std::vector<Scene*> activeScenes;
	std::vector<Scene*> allScenes;
};
