#include "Renderer.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

	return true;
}

void loadStartingAssets()
{
    AssetManager::getInstance().initialize();
    AssetManager::getInstance().loadTextureFile("pepe_kid_sad");
}

void loadStartingScene()
{
    SceneManager::getInstance().initialize();
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
    Texture* tex1 = AssetManager::getInstance().getTexture("pepe_kid_sad");
    Texture* tex2 = AssetManager::getInstance().getTexture("pepe_kid_sad");
    Texture* tex3 = AssetManager::getInstance().getTexture("pepe_kid_sad");
    Texture* tex4 = AssetManager::getInstance().getTexture("pepe_kid_sad");

    unsigned int scene1 = tex1->getRendererID();
    unsigned int scene2 = tex2->getRendererID();
    unsigned int scene3 = tex3->getRendererID();
    unsigned int scene4 = tex4->getRendererID();
	
    ImGui::Begin("Control Panel");
    if (ImGui::ImageButton((void*)(intptr_t)scene1, ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
    {
        SceneManager::getInstance().loadSceneAsync(0);
    }
    if (ImGui::ImageButton((void*)(intptr_t)scene2, ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
    {
        SceneManager::getInstance().loadSceneAsync(1);
    }
    if (ImGui::ImageButton((void*)(intptr_t)scene3, ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
    {
        SceneManager::getInstance().loadSceneAsync(2);
    }
    if (ImGui::ImageButton((void*)(intptr_t)scene4, ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
    {
        SceneManager::getInstance().loadSceneAsync(3);
    }
    ImGui::End();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        SceneManager::getInstance().unloadScene(0);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        SceneManager::getInstance().unloadScene(1);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        SceneManager::getInstance().unloadScene(2);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        SceneManager::getInstance().unloadScene(3);
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
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    	
	renderGameObjects();
	renderUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
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
    	
        AssetManager::getInstance().instantiateNewLoadedMeshes();
        AssetManager::getInstance().generateNewLoadedTextures();
        SceneManager::getInstance().instantiateNewLoadedScenes();
    	
        processInput(window);
        update();
        render();
    }
}

void shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
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
