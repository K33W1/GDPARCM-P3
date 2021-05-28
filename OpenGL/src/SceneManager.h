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

	void toggleScene(int index);
	void loadSceneAsMain(int index);
	void loadScene(int index);
	void loadScene(Scene* scene);
	void loadSceneAsync(int index);
	void loadSceneAsMainAsync(int index);
	void loadAllScenesAsync();
	void unloadScene(int index);
	void unloadSceneAsync(int index);
	
	void instantiateNewLoadedScenes();

	Scene* getScene(int index) const;
	Scene* getMainScene() const;
	const std::vector<Scene*>& getActiveScenes();

private:
	SceneManager() = default;
	~SceneManager() override = default;
	
	ThreadSafeVector<Scene*> newLoadedScenes;
	std::vector<Scene*> activeScenes;
	std::vector<Scene*> allScenes;
	Scene* mainLoadingScene;
};
