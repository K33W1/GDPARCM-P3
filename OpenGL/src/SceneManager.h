#pragma once
#include "Singleton.h"
#include "ThreadSafeVector.h"
#include <vector>

class Scene;
class SceneLoadingThread;

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	void initialize();

	void instantiateNewLoadedScenes();

	void loadScene(int index);
	void loadSceneAsync(int index);
	void unloadScene(int index);

	Scene* getScene(int index) const;
	const std::vector<Scene*>& getActiveScenes();

private:
	SceneManager() = default;
	~SceneManager() override = default;

	ThreadSafeVector<SceneLoadingThread*> sceneLoadingThreads;
	ThreadSafeVector<Scene*> newLoadedScenes;
	std::vector<Scene*> activeScenes;
	std::vector<Scene*> allScenes;
};
