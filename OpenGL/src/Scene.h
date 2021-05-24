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

	void loadAssets();
	void loadGameObjects();
	
	void unloadGameObjects();
	void unloadAssets();
	
	const std::vector<GameObject*> getGameObjects() const;

protected:
	void addGameObject(GameObject* gameObject);

	std::vector<std::string> assets;

private:
	std::vector<GameObject*> gameObjects;
};
