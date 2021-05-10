#include "GameObject.h"
#include <glm/ext/matrix_transform.hpp>

GameObject::GameObject(const VertexArray& va, const IndexBuffer& ib, Shader& shader)
	: va(va), ib(ib), shader(shader)
{
	this->transform = glm::mat4(1.0f);
}

void GameObject::setPosition(const glm::vec3& newPosition)
{
	this->transform[3].x = newPosition.x;
	this->transform[3].y = newPosition.y;
	this->transform[3].z = newPosition.z;
}

const VertexArray& GameObject::getVertexArray() const
{
	return this->va;
}

const IndexBuffer& GameObject::getIndexBuffer() const
{
	return this->ib;
}

Shader& GameObject::getShader() const
{
	return this->shader;
}

glm::mat4 GameObject::getModelMatrix() const
{
	return this->transform;
}

glm::vec3 GameObject::getPosition() const
{
	return glm::vec3(this->transform[3]);
}
