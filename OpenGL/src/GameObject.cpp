#include "GameObject.h"
#include <glm/ext/matrix_transform.hpp>

GameObject::GameObject(const Mesh* const mesh, Shader* const shader)
	: mesh(mesh), shader(shader), position(0.0f), scale(1.0f)
{

}

void GameObject::setPosition(const glm::vec3& newPosition)
{
	position = newPosition;
}

void GameObject::setScale(const glm::vec3& newScale)
{
	scale = newScale;
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
	return glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 GameObject::getPosition() const
{
	return position;
}
