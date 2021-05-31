#pragma once
#include "Singleton.h"
#include "ThreadSafeVector.h"
#include <vector>

class SceneUnloadingThread;
class Scene;
class SceneLoadingThread;

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	void initialize();

	void switchToScene(int index);
	void loadScene(int index, bool loadAsEnabled);
	void loadScene(Scene* scene, bool loadAsEnabled);
	void loadSceneAsync(int index, bool loadAsEnabled);
	void loadAllScenesAsync(bool loadAsEnabled);
	void unloadScene(int index);
	void unloadSceneAsync(int index);
	
	void instantiateNewLoadedScenes();

	Scene* getScene(int index) const;
	Scene* getMainLoadingScene();
	const std::vector<Scene*>& getEnabledScenes() const;

	void deleteSceneLoadingThread(SceneLoadingThread* thread);
	void deleteSceneUnloadingThread(SceneUnloadingThread* thread);

	float getMainProgressBarPercent();

private:
	SceneManager() = default;
	~SceneManager() override = default;

	void enableScene(Scene* scene);
	void disableScene(Scene* scene);

	ThreadSafeVector<SceneLoadingThread*> sceneLoadingThreads;
	ThreadSafeVector<SceneUnloadingThread*> sceneUnloadingThreads;
	ThreadSafeVector<Scene*> newLoadedScenesAsEnabled;
	ThreadSafeVector<Scene*> newLoadedScenesAsDisabled;
	std::vector<Scene*> enabledScenes;
	std::vector<Scene*> disabledScenes;
	std::vector<Scene*> allScenes;
	int sceneLoadingCount;
};
