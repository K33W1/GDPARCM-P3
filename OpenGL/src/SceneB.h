#pragma once
#include "Scene.h"

class SceneB : public Scene
{
public:
	SceneB();

	void loadAssets() override;
	void loadGameObjects() override;
	void unloadAssets() override;
};
