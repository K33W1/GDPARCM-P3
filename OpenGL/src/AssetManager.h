#pragma once
#include "Singleton.h"
#include <string>
#include <unordered_map>

class AssetManager : public Singleton<AssetManager>
{
	friend class Singleton<AssetManager>;

public:
	void initialize();
	
};

