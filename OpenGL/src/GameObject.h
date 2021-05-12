#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject(const Mesh* const mesh, Shader* const shader);

	void setPosition(const glm::vec3& newPosition);

	const Mesh* const getMesh() const;
	Shader* const getShader() const;
	
	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;

private:
	const Mesh* const mesh;
	Shader* const shader;

	glm::mat4 transform;
};

