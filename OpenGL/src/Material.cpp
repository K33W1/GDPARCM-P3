#include "Material.h"
#include "Shader.h"
#include "Texture.h"

Material::Material(Shader* shader, Texture* diffuseTexture, const glm::vec4& diffuseColor)
	: shader(shader), diffuseTexture(diffuseTexture), diffuseColor(diffuseColor)
{
	
}

void Material::bind()
{
	shader->bind();
	diffuseTexture->bind();
	shader->setUniform1i("u_Texture", 0);
	shader->setUniform4f("u_Color", diffuseColor.x, diffuseColor.y, diffuseColor.z, diffuseColor.w);
}

void Material::unbind()
{
	shader->unbind();
	diffuseTexture->unbind();
}

void Material::setShaderMVP(const glm::mat4& mvp)
{
	shader->setUniformMat4f("u_MVP", mvp);
}

Shader* Material::getShader() const
{
	return shader;
}
