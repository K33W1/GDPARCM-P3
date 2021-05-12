#include "GameObject.h"
#include <glm/ext/matrix_transform.hpp>

GameObject::GameObject(const Mesh* const mesh, Shader* const shader)
	: mesh(mesh), shader(shader)
{
	this->transform = glm::mat4(1.0f);
}

void GameObject::setPosition(const glm::vec3& newPosition)
{
	this->transform[3].x = newPosition.x;
	this->transform[3].y = newPosition.y;
	this->transform[3].z = newPosition.z;
}

const Mesh* const GameObject::getMesh() const
{
	return mesh;
}

Shader* const GameObject::getShader() const
{
	return shader;
}

glm::mat4 GameObject::getModelMatrix() const
{
	return transform;
}

glm::vec3 GameObject::getPosition() const
{
	return glm::vec3(transform[3]);
}
