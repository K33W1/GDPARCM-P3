#pragma once
#include "Singleton.h"
#include "ThreadSafeVector.h"
#include "ThreadSafeUnorderedMap.h"
#include "MeshData.h"
#include "TextureData.h"
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Mesh;
class Texture;
class Material;
class Shader;

class AssetManager : public Singleton<AssetManager>
{
	friend class Singleton<AssetManager>;

public:
	void initialize();

	void loadMeshFile(const std::string& filename);
	void loadTextureFile(const std::string& filepath);
	void loadShaderFile(const std::string& filepath);

	void createMaterial(const std::string& name, Shader* shader, Texture* texture, const glm::vec4& color);

	void instantiateNewLoadedMeshes();
	void generateNewLoadedTextures();
	
	bool isMeshLoaded(const std::string& name);
	bool isTextureLoaded(const std::string& name);

	Mesh* const getMesh(const std::string& name);
	Texture* const getTexture(const std::string& name);
	Shader* const getShader(const std::string& name);
	Material* const getMaterial(const std::string& name);

private:
	~AssetManager() override;

	void loadPrimitiveMeshes();

	std::string getFileName(const std::string& name);

	ThreadSafeVector<MeshData> meshesToInstantiate;
	ThreadSafeVector<TextureData> texturesToGenerate;
	ThreadSafeUnorderedMap<std::string, Mesh* const> meshes;
	ThreadSafeUnorderedMap<std::string, Texture* const> textures;
	ThreadSafeUnorderedMap<std::string, Shader* const> shaders;
	ThreadSafeUnorderedMap<std::string, Material* const> materials;

	const std::string MESH_PATH = "res/meshes/";
	const std::string TEXTURE_PATH = "res/textures/";
};