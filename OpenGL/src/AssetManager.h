#pragma once
#include "Singleton.h"
#include "ThreadSafeVector.h"
#include "ThreadSafeUnorderedMap.h"
#include "MeshData.h"
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

	void loadMeshFile(const std::string& filepath);
	void loadMeshFileAsync(const std::string& filepath);
	void loadMeshFileAsyncImpl(const std::string& filepath);
	void loadTextureFile(const std::string& filepath);
	void loadTextureFileAsync(const std::string& filepath);
	void loadTextureFileAsyncImpl(const std::string& filepath);
	void loadShaderFile(const std::string& filepath);

	void instantiateNewLoadedAssets();

	bool isMeshLoaded(const std::string& name);
	bool isTextureLoaded(const std::string& name);

	Mesh* const getMesh(const std::string& name);
	Texture* const getTexture(const std::string& name);
	Shader* const getShader(const std::string& name);

private:
	~AssetManager() override;

	void loadPrimitiveMeshes();

	std::string getFileName(const std::string& name);

	ThreadSafeVector<MeshData> meshesToInstantiate;
	ThreadSafeUnorderedMap<std::string, Mesh* const> meshes;
	ThreadSafeUnorderedMap<std::string, Texture* const> textures;
	std::unordered_map<std::string, Shader* const> shaders;
};
