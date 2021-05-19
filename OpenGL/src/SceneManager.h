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
	SceneManager();

	void initialize();

	void startNewlyLoadedScenes();

	void loadScene(int index);
	void loadSceneAsync(int index);
	void unloadScene(int index);

	const std::vector<const Scene*> getActiveScenes() const;

private:
	~SceneManager() override;

	void loadSceneAsyncImpl(int index);

	std::vector<std::thread*> loadingSceneThreads;
	ThreadSafeVector<const Scene*> newlyLoadedScenes;
	std::vector<const Scene*> activeScenes;
	std::vector<Scene*> allScenes;
};
