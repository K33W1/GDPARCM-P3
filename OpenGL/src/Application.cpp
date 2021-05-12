#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "AssetManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <iostream>
#include <sstream>

GLFWwindow* window;
Renderer renderer;
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

std::vector<GameObject> gameObjects;

bool initialize()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Error!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error!" << std::endl;
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

	return true;
}

void loadAssets()
{
    return;
}

void renderGameObjects()
{
	// Makeshift camera - Projection and view matrices can be wrapped around a class
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 viewProj = proj * view;
	
    for (const GameObject& gameObject : gameObjects)
    {
        Shader* shader = gameObject.getShader();
    	
        glm::mat4 mvp = viewProj * gameObject.getModelMatrix();
    	
        shader->bind();
        shader->setUniformMat4f("u_MVP", mvp);
    	
        renderer.draw(gameObject, shader);
    }
}

void renderUI()
{
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    // TODO: There's "update" behaviour inside the render function which is weird
    glm::vec3 pos1 = gameObjects[0].getPosition();

    ImGui::SliderFloat3("Translation A", &pos1.x, -500.0f, 500.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    gameObjects[0].setPosition(pos1);
}

void run()
{
    AssetManager& assetManager = AssetManager::getInstance();
	
    assetManager.initialize();
	
    gameObjects.emplace_back(assetManager.getMesh("teapot"), assetManager.getShader("basic"));
    gameObjects[0].setPosition({ 0.0f, 0.0f, -250.0f });

    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();
        ImGui_ImplGlfwGL3_NewFrame();
    	
        renderGameObjects();
        renderUI();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    	
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void shutdown()
{
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

int main()
{
	if (!initialize())
        return -1;

    loadAssets();
    run();
    shutdown();
}
