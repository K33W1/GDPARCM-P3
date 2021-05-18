#pragma once
#include <vector>

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void load() = 0;
	void unload();
	
	const std::vector<GameObject*> getGameObjects() const;

protected:
	void addGameObject(GameObject* gameObject);

private:
	std::vector<GameObject*> gameObjects;
};
