#include "Renderer.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "Random.h"
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

// Camera
Camera camera;
bool firstMouse = true;
bool isMouseDown = false;
float lastX = WINDOW_WIDTH * 0.5f;
float lastY = WINDOW_HEIGHT * 0.5f;

// Callbacks
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mousePositionCallback(GLFWwindow* window, double posX, double posY);
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
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);
    glfwSetScrollCallback(window, scrollCallback);

	return true;
}

void loadStartingAssets()
{
    AssetManager::getInstance().initialize();
    AssetManager::getInstance().loadTextureFile("pepe_kid_sad");
    AssetManager::getInstance().loadTextureFile("pepe_kid_celebrate");
    AssetManager::getInstance().loadTextureFile("pepe_nervous");
    AssetManager::getInstance().loadTextureFile("pepe_celebrate");
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
    SceneManager& sceneManager = SceneManager::getInstance();
	
    int windowSizeX;
    int windowSizeY;
    glfwGetWindowSize(window, &windowSizeX, &windowSizeY);
    ImVec2 buttonUv0 = ImVec2(0, 1);
    ImVec2 buttonUv1 = ImVec2(1, 0);
    Texture* tex1 = AssetManager::getInstance().getTexture("pepe_kid_sad");
    Texture* tex2 = AssetManager::getInstance().getTexture("pepe_kid_celebrate");
    Texture* tex3 = AssetManager::getInstance().getTexture("pepe_nervous");
    Texture* tex4 = AssetManager::getInstance().getTexture("pepe_celebrate");
    unsigned int tex1Id = tex1->getRendererID();
    unsigned int tex2Id = tex2->getRendererID();
    unsigned int tex3Id = tex3->getRendererID();
    unsigned int tex4Id = tex4->getRendererID();
	
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(windowSizeX, 192));
    ImGui::Begin("Scene Viewer");
    if (ImGui::ImageButton((void*)(intptr_t)tex1Id, ImVec2(128, 128), buttonUv0, buttonUv1))
    {
        sceneManager.loadSceneAsync(0);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex2Id, ImVec2(128, 128), buttonUv0, buttonUv1))
    {
        sceneManager.loadSceneAsync(1);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex3Id, ImVec2(128, 128), buttonUv0, buttonUv1))
    {
        sceneManager.loadSceneAsync(2);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex4Id, ImVec2(128, 128), buttonUv0, buttonUv1))
    {
        sceneManager.loadSceneAsync(3);
    }

    float progress1 = sceneManager.getScene(0)->getPercentLoaded();
    float progress2 = sceneManager.getScene(1)->getPercentLoaded();
    float progress3 = sceneManager.getScene(2)->getPercentLoaded();
    float progress4 = sceneManager.getScene(3)->getPercentLoaded();

    ImGui::ProgressBar(progress1, ImVec2(136, 16));
    ImGui::SameLine(0, 32);
    ImGui::ProgressBar(progress2, ImVec2(136, 16));
    ImGui::SameLine(0, 32);
    ImGui::ProgressBar(progress3, ImVec2(136, 16));
    ImGui::SameLine(0, 32);
    ImGui::ProgressBar(progress4, ImVec2(136, 16));
    
    ImGui::End();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

	// Unload scenes
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        SceneManager::getInstance().unloadScene(0);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        SceneManager::getInstance().unloadScene(1);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        SceneManager::getInstance().unloadScene(2);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        SceneManager::getInstance().unloadScene(3);
    }

	// Camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
    	if (action == GLFW_PRESS)
    	{
			isMouseDown = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    	}
        else if (action == GLFW_RELEASE)
        {
            isMouseDown = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void mousePositionCallback(GLFWwindow* window, double dPosX, double dPosY)
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

    if (isMouseDown)
    {
        camera.processMouseMovement(xoffset, yoffset);
    }
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

    Random::seed(std::chrono::system_clock::now().time_since_epoch().count());
	
    loadStartingAssets();
    loadStartingScene();
    run();
    shutdown();
}
