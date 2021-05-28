#pragma once
#include <string>
#include <mutex>
#include "ThreadSafeVector.h"

class GameObject;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void loadAssets();
	void loadGameObjects();
	
	void unloadGameObjects();
	void unloadAssets();

	void manualSharedLockGameObjects();
	void manualSharedUnlockGameObjects();
	
	ThreadSafeVector<GameObject*>& getGameObjects();
	bool isLoaded();
	float getPercentLoaded();

protected:
	void addAsset(const std::string& assetName);

private:
	ThreadSafeVector<std::string> assets;
	ThreadSafeVector<GameObject*> gameObjects;
	int assetsLoaded;
};
