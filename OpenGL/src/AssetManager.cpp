#include "AssetManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <tinyobjloader/tiny_obj_loader.h>
#include <iostream>

void AssetManager::initialize()
{
	loadPrimitiveMeshes();
	loadMeshFiles();

	Shader* shader = new Shader("res/shaders/Basic.shader");
	shader->bind();
	shader->unbind();

	Texture* texture = new Texture("res/textures/pepe_kid_sad.png");
	texture->bind();
	shader->setUniform1i("u_Texture", 0);

	textures.emplace("pepe", texture);
	shaders.emplace("basic", shader);
}

void AssetManager::loadMeshFiles()
{
	std::string inputfile = "res/meshes/teapot.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if (!err.empty())
	{
		std::cerr << err;
	}

	if (!ret)
	{
		std::cout << "Failed to load mesh! File: " << inputfile << '\n';
		return;
	}

	// Loop over shapes
	for (const tinyobj::shape_t& shape : shapes)
	{
		// Vertex Data
		std::vector<float> vertexData;
		for (int i = 0; i < attrib.vertices.size() / 3; i++)
		{
			vertexData.push_back(attrib.vertices[i * 3 + 0]);
			vertexData.push_back(attrib.vertices[i * 3 + 1]);
			vertexData.push_back(attrib.vertices[i * 3 + 2]);
			vertexData.push_back(attrib.texcoords[i * 2 + 0]);
			vertexData.push_back(attrib.texcoords[i * 2 + 1]);
		}
		
		// Indices
		std::vector<unsigned int> indices;
		for (int i = 0; i < shape.mesh.indices.size(); i++)
		{
			indices.push_back(shape.mesh.indices[i].vertex_index);
		}

		VertexArray* va = new VertexArray();
		VertexBuffer* vb = new VertexBuffer(&vertexData[0], vertexData.size() * sizeof(size_t));
		VertexBufferLayout* layout = new VertexBufferLayout();
		layout->push<float>(3);
		layout->push<float>(2);
		va->bind();
		va->setBuffer(vb, layout);
		IndexBuffer* ib = new IndexBuffer(&indices[0], (int)indices.size());

		meshes.emplace("teapot", new Mesh(va, ib));

		std::cout << "Added mesh: " << shape.name << '\n';
	}
}

void AssetManager::loadPrimitiveMeshes()
{
	float positions[] =
	{
		-100.0f, -100.0f, 0.0f, 0.0f,
		 200.0f, -100.0f, 1.0f, 0.0f,
		 200.0f,  200.0f, 1.0f, 1.0f,
		-100.0f,  200.0f, 0.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexArray* va = new VertexArray();
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(2);
	layout->push<float>(2);
	va->setBuffer(vb, layout);
	IndexBuffer* ib = new IndexBuffer(indices, 6);

	Mesh* quad = new Mesh(va, ib);

	va->unbind();
	vb->unbind();
	ib->unbind();

	meshes.emplace("quad", quad);
}

const Mesh* const AssetManager::getMesh(const std::string& name) const
{
	return meshes.at(name);
}

const Texture* const AssetManager::getTexture(const std::string& name) const
{
	return textures.at(name);
}

Shader* const AssetManager::getShader(const std::string& name) const
{
	return shaders.at(name);
}

AssetManager::~AssetManager()
{
	for (const auto& meshItr : meshes)
	{
		delete meshItr.second;
	}

	for (const auto& textureItr : textures)
	{
		delete textureItr.second;
	}

	for (const auto& shaderItr : shaders)
	{
		delete shaderItr.second;
	}
}
