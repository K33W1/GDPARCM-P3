#pragma once
#include "Scene.h"

class SceneA : public Scene
{
public:
	SceneA();
	
	void loadAssets() override;
	void loadGameObjects() override;
	void unloadAssets() override;
};
