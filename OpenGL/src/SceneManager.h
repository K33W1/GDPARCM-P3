#pragma once
#include "Singleton.h"
#include <vector>

class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	SceneManager();
	~SceneManager();

	void initialize();

	void loadScene(int index);
	void unloadScene(int index);

	const std::vector<const Scene*> getLoadedScenes() const;

private:
	std::vector<const Scene*> loadedScenes;
	std::vector<Scene*> allScenes;
};

