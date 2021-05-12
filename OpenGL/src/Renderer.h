#pragma once
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class GameObject;
class Shader;

class Renderer
{
public:
    Renderer();
	
    void clear() const;
    void draw(const GameObject& gameObject, Shader* const shader);
};
