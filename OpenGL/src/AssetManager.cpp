#include "AssetManager.h"
#include "Mesh.h"
#include "MeshData.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"
#include <tinyobjloader/tiny_obj_loader.h>
#include <iostream>
#include <thread>

void AssetManager::initialize()
{
	loadPrimitiveMeshes();

	loadShaderFile("res/shaders/textured.shader");
	loadTextureFile("res/textures/pepe_kid_sad.png");
	loadTextureFile("res/textures/Bulbasaur.png");
	loadTextureFile("res/textures/controller_red.png");
	
	Shader* shader = getShader("textured");
	Texture* bulbasaurTexture = getTexture("Bulbasaur");

	createMaterial("Bulbasaur", shader, bulbasaurTexture, glm::vec4(1.0f));
}

void AssetManager::loadMeshFile(const std::string& filepath)
{
	std::string err;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> tinyMaterials;
	
	bool ret = tinyobj::LoadObj(shapes, tinyMaterials, err, filepath.c_str(), filepath.c_str());

	if (!err.empty())
	{
		std::cerr << err;
	}

	if (!ret)
	{
		std::cout << "Failed to load mesh! File: " << filepath << '\n';
		return;
	}

	// TODO: Load submeshes
	
	// Loop over shapes
	for (const tinyobj::shape_t& shape : shapes)
	{
		const tinyobj::mesh_t& mesh = shape.mesh;
		std::vector<float> vertexData;

		// Extract data
		for (size_t i = 0; i < mesh.positions.size() / 3; i++)
		{
			vertexData.push_back(mesh.positions[3 * i + 0]);
			vertexData.push_back(mesh.positions[3 * i + 1]);
			vertexData.push_back(mesh.positions[3 * i + 2]);
			vertexData.push_back(mesh.texcoords[2 * i + 0]);
			vertexData.push_back(mesh.texcoords[2 * i + 1]);
		}

		meshesToInstantiate.push_back({ filepath, vertexData, mesh.indices });

		break; // Load only the first submesh
	}
}

void AssetManager::loadMeshFileAsync(const std::string& filepath)
{
	
}

void AssetManager::loadTextureFile(const std::string& filepath)
{
	textures.emplace(getFileName(filepath), new Texture(filepath));
}

void AssetManager::loadTextureFileAsync(const std::string& filepath)
{
	
}

void AssetManager::loadShaderFile(const std::string& filepath)
{
	shaders.emplace(getFileName(filepath), new Shader(filepath));
}

void AssetManager::instantiateNewLoadedAssets()
{
	for (const MeshData& meshData : meshesToInstantiate)
	{
		const auto& vertexData = meshData.getVertexData();
		const auto& indices = meshData.getIndices();
		const auto& fileName = getFileName(meshData.getFilePath());

		VertexArray* va = new VertexArray();
		IndexBuffer* ib = new IndexBuffer(&indices[0], (int)indices.size());
		VertexBuffer* vb = new VertexBuffer(&vertexData[0], vertexData.size() * sizeof(float));
		VertexBufferLayout* layout = new VertexBufferLayout();
		layout->push<float>(3);
		layout->push<float>(2);
		va->setBuffer(vb, layout);

		meshes.emplace(fileName, new Mesh(va, ib));

		std::cout << "Added mesh: " << fileName << '\n';
	}

	meshesToInstantiate.clear();
}

void AssetManager::loadPrimitiveMeshes()
{
	float positions[] =
	{
		-50.0f, -50.0f, 0.0f, 0.0f,
		 50.0f, -50.0f, 1.0f, 0.0f,
		 50.0f,  50.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexArray* va = new VertexArray();
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(2);
	layout->push<float>(2);
	va->setBuffer(vb, layout);

	Mesh* quad = new Mesh(va, ib);
	
	meshes.emplace("quad", quad);
}

void AssetManager::createMaterial(const std::string& name, Shader* shader, Texture* texture, const glm::vec4& color)
{
	materials.emplace(name, new Material(shader, texture, color));
}

std::string AssetManager::getFileName(const std::string& name)
{
	std::string fileNameExt = name.substr(name.find_last_of('/') + 1);
	std::string fileName = fileNameExt.substr(0, fileNameExt.find_last_of('.'));
	return fileName;
}

bool AssetManager::isMeshLoaded(const std::string& name)
{
	return meshes.doesExist(name);
}

bool AssetManager::isTextureLoaded(const std::string& name)
{
	return textures.doesExist(name);
}

Mesh* const AssetManager::getMesh(const std::string& name)
{
	return meshes.at(name);
}

Texture* const AssetManager::getTexture(const std::string& name)
{
	return textures.at(name);
}

Shader* const AssetManager::getShader(const std::string& name)
{
	return shaders.at(name);
}

Material* const AssetManager::getMaterial(const std::string& name)
{
	return materials.at(name);
}

AssetManager::~AssetManager()
{
	for (const auto& nameMeshPair : meshes)
	{
		delete nameMeshPair.second;
	}

	for (const auto& nameTexturePair : textures)
	{
		delete nameTexturePair.second;
	}

	for (const auto& nameShaderPair : shaders)
	{
		delete nameShaderPair.second;
	}
	
	for (const auto& nameMaterialPair : materials)
	{
		delete nameMaterialPair.second;
	}
}
