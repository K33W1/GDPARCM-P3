#pragma once
#include <glm/glm.hpp>

class Shader;
class Texture;

class Material
{
public:
	Material(Shader* shader, Texture* diffuseTexture, const glm::vec4& diffuseColor);
	~Material() = default;

	void bind();
	void unbind();

	void setShaderMVP(const glm::mat4& mvp);

	Shader* getShader() const;

private:
	Shader* const shader;
	Texture* const diffuseTexture;
	glm::vec4 diffuseColor;
};
