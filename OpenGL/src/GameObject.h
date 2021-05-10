#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject(const VertexArray& va, const IndexBuffer& ib, Shader& shader);

	void setPosition(const glm::vec3& newPosition);

	const VertexArray& getVertexArray() const;
	const IndexBuffer& getIndexBuffer() const;
	Shader& getShader() const;

	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;

private:
	const VertexArray& va;
	const IndexBuffer& ib;
	Shader& shader;

	glm::mat4 transform;
};

