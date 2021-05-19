#pragma once
#include "Singleton.h"
#include <string>
#include <unordered_map>

class Mesh;
class Texture;
class Shader;

class AssetManager : public Singleton<AssetManager>
{
	friend class Singleton<AssetManager>;

public:
	void initialize();

	void loadMeshFiles();
	void loadPrimitiveMeshes();

	const Mesh* const getMesh(const std::string& name) const;
	const Texture* const getTexture(const std::string& name) const;
	Shader* const getShader(const std::string& name) const;

private:
	~AssetManager() override;
	
	std::unordered_map<std::string, const Mesh* const> meshes;
	std::unordered_map<std::string, const Texture* const> textures;
	std::unordered_map<std::string, Shader* const> shaders;
};
