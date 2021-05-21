#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <iostream>

#include "Material.h"

GLFWwindow* window;
Renderer renderer;
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera;

bool firstMouse = true;
float lastX = WINDOW_WIDTH * 0.5f;
float lastY = WINDOW_HEIGHT * 0.5f;

void mouseCallback(GLFWwindow* window, double posX, double posY);
void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);

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
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    // glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

	return true;
}

void loadStartingAssets()
{
    AssetManager::getInstance().initialize();
}

void loadStartingScene()
{
	SceneManager& sceneManager = SceneManager::getInstance();
    sceneManager.initialize();
    sceneManager.loadSceneAsync(0);
}

void renderGameObjects()
{
    glm::mat4 viewProj = camera.getProjectionMatrix() * camera.getViewMatrix();

    for (Scene* scene : SceneManager::getInstance().getActiveScenes())
    {
        for (GameObject* gameObject : scene->getGameObjects())
        {
            Material* const material = gameObject->getMaterial();
            glm::mat4 mvp = viewProj * gameObject->getModelMatrix();

            material->bind();
            material->setShaderMVP(mvp);
            
            renderer.draw(gameObject, material->getShader());
        }
    }
}

void renderUI()
{
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    // TODO: There's "update" behaviour inside the render function which is weird
    if (SceneManager::getInstance().getActiveScenes().size() == 0)
        return;

    Scene* const scene = SceneManager::getInstance().getActiveScenes()[0];

	for (int i = 0; i < scene->getGameObjects().size(); i++)
	{
        GameObject* gameobject = scene->getGameObjects()[i];
        glm::vec3 pos = gameobject->getPosition();

        std::string sliderName = "Translation " + std::to_string(i);
		
        ImGui::SliderFloat3(sliderName.c_str(), &pos.x, -200.0f, 200.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        gameobject->setPosition(pos);
	}
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouseCallback(GLFWwindow* window, double dPosX, double dPosY)
{
    float posX = (float)dPosX;
    float posY = (float)dPosY;
	
    if (firstMouse)
    {
        lastX = posX;
        lastY = posY;
        firstMouse = false;
    }

    float xoffset = posX - lastX;
    float yoffset = lastY - posY;
    lastX = posX;
    lastY = posY;

    camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
    camera.processMouseScroll((float)offsetY);
}

void update()
{
    for (Scene* scene : SceneManager::getInstance().getActiveScenes())
    {
        for (GameObject* gameObject : scene->getGameObjects())
        {
            glm::vec3 rot = gameObject->getRotation();
            rot.y += 100.0f * deltaTime;
            gameObject->setRotation(rot);
        }
    }
}

void render()
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

void run()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    	
        AssetManager::getInstance().instantiateNewLoadedAssets();
        SceneManager::getInstance().instantiateNewLoadedScenes();
    	
        processInput(window);
        update();
        render();
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

    loadStartingAssets();
    loadStartingScene();
    run();
    shutdown();
}
