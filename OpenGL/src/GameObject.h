#pragma once
#include <glm/glm.hpp>

class Mesh;
class Material;

class GameObject
{
public:
	GameObject(Mesh* mesh, Material* material);

	void setPosition(const glm::vec3& newPosition);
	void setRotation(const glm::vec3& newRotation);
	void setScale(const glm::vec3& newScale);

	Mesh* getMesh() const;
	Material* getMaterial() const;
	
	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;

private:
	Mesh* const mesh;
	Material* const material;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

