#pragma once
#include <vector>
#include <string>
#include <chrono>

class GameObject;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void loadAssets() = 0;
	virtual void loadGameObjects() = 0;
	
	void unloadGameObjects();
	virtual void unloadAssets() = 0;
	
	const std::vector<GameObject*> getGameObjects() const;

protected:
	void addGameObject(GameObject* gameObject);

	std::vector<std::string> assets;

private:
	std::vector<GameObject*> gameObjects;
};
