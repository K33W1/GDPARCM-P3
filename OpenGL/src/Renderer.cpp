#include "Renderer.h"
#include "GameObject.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): "
            << function
            << " "
            << file
            << ": "
            << line
            << std::endl;
        return false;
    }

    return true;
}

Renderer::Renderer()
{
	
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const GameObject* gameObject, Shader* const shader)
{
    const Mesh* const mesh = gameObject->getMesh();
    const VertexArray* const va = mesh->getVertexArray();
    const IndexBuffer* const ib = mesh->getIndexBuffer();
	
    va->bind();
    ib->bind();
    shader->bind();
	
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
}
