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
    AssetManager::getInstance().loadTextureFile("scene_1");
    AssetManager::getInstance().loadTextureFile("scene_2");
    AssetManager::getInstance().loadTextureFile("scene_3");
    AssetManager::getInstance().loadTextureFile("scene_4");
    AssetManager::getInstance().loadTextureFile("scene_5");
    AssetManager::getInstance().loadTextureFile("xbutton");
}

void loadStartingScene()
{
    SceneManager::getInstance().initialize();
    SceneManager::getInstance().loadSceneAsync(0, false);
    SceneManager::getInstance().loadSceneAsync(1, false);
    SceneManager::getInstance().loadSceneAsync(2, false);
    SceneManager::getInstance().loadSceneAsync(3, false);
    SceneManager::getInstance().loadSceneAsync(4, false);
}

void renderGameObjects()
{
    glm::mat4 viewProj = camera.getProjectionMatrix() * camera.getViewMatrix();

    for (Scene* scene : SceneManager::getInstance().getEnabledScenes())
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
    Scene* scene1 = sceneManager.getScene(0);
    Scene* scene2 = sceneManager.getScene(1);
    Scene* scene3 = sceneManager.getScene(2);
    Scene* scene4 = sceneManager.getScene(3);
    Scene* scene5 = sceneManager.getScene(4);
	
    int glfwWindowSizeX;
    int glfwWindowSizeY;
    glfwGetWindowSize(window, &glfwWindowSizeX, &glfwWindowSizeY);
    ImVec2 buttonUv0 = ImVec2(0, 1);
    ImVec2 buttonUv1 = ImVec2(1, 0);
    ImVec4 buttonBgColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 buttonSceneDisabledTint = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);
    ImVec4 buttonSceneEnabledTint = ImVec4(0.75f, 0.9f, 0.75f, 0.75f);
	
    Texture* tex1 = AssetManager::getInstance().getTexture("scene_1");
    Texture* tex2 = AssetManager::getInstance().getTexture("scene_2");
    Texture* tex3 = AssetManager::getInstance().getTexture("scene_3");
    Texture* tex4 = AssetManager::getInstance().getTexture("scene_4");
    Texture* tex5 = AssetManager::getInstance().getTexture("scene_5");
    Texture* xtex = AssetManager::getInstance().getTexture("xbutton");
	
    unsigned int tex1Id = tex1->getRendererID();
    unsigned int tex2Id = tex2->getRendererID();
    unsigned int tex3Id = tex3->getRendererID();
    unsigned int tex4Id = tex4->getRendererID();
    unsigned int tex5Id = tex5->getRendererID();
    unsigned int xtexId = xtex->getRendererID();
	
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(glfwWindowSizeX, 192));
    ImGui::Begin("Scene Viewer");
    if (ImGui::ImageButton((void*)(intptr_t)tex1Id, ImVec2(128, 128), buttonUv0, buttonUv1, -1, buttonBgColor, scene1->getSceneState() == SceneState::Enabled ? buttonSceneEnabledTint : buttonSceneDisabledTint))
    {
        sceneManager.switchToScene(0);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex2Id, ImVec2(128, 128), buttonUv0, buttonUv1, -1, buttonBgColor, scene2->getSceneState() == SceneState::Enabled ? buttonSceneEnabledTint : buttonSceneDisabledTint))
    {
        sceneManager.switchToScene(1);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex3Id, ImVec2(128, 128), buttonUv0, buttonUv1, -1, buttonBgColor, scene3->getSceneState() == SceneState::Enabled ? buttonSceneEnabledTint : buttonSceneDisabledTint))
    {
        sceneManager.switchToScene(2);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex4Id, ImVec2(128, 128), buttonUv0, buttonUv1, -1, buttonBgColor, scene4->getSceneState() == SceneState::Enabled ? buttonSceneEnabledTint : buttonSceneDisabledTint))
    {
        sceneManager.switchToScene(3);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::ImageButton((void*)(intptr_t)tex5Id, ImVec2(128, 128), buttonUv0, buttonUv1, -1, buttonBgColor, scene5->getSceneState() == SceneState::Enabled ? buttonSceneEnabledTint : buttonSceneDisabledTint))
    {
        sceneManager.switchToScene(4);
    }
    ImGui::SameLine(0, 32);
    if (ImGui::Button("View All", ImVec2(128, 128)))
    {
        sceneManager.loadAllScenesAsync(true);
    }

	// Display loading bars or X buttons
    float progress1 = scene1->getPercentLoaded();
    float progress2 = scene2->getPercentLoaded();
    float progress3 = scene3->getPercentLoaded();
    float progress4 = scene4->getPercentLoaded();
    float progress5 = scene5->getPercentLoaded();
    const ImVec2 progressBarSize = ImVec2(136, 16);
    const ImVec2 xButtonSize = ImVec2(128, 16);

    if (scene1->getSceneState() == SceneState::Unloaded)
    {
        ImGui::Dummy(progressBarSize);
    }
    else if (scene1->getSceneState() == SceneState::Loading)
    {
        ImGui::ProgressBar(progress1, progressBarSize);
    }
    else if (scene1->getSceneState() == SceneState::Disabled || scene1->getSceneState() == SceneState::Enabled)
    {
        ImGui::PushID("UnloadButton1");
        if (ImGui::ImageButton((void*)(intptr_t)xtexId, xButtonSize, buttonUv0, buttonUv1))
        {
            SceneManager::getInstance().unloadSceneAsync(0);
        }
        ImGui::PopID();
    }
    ImGui::SameLine(0, 32);
    if (scene2->getSceneState() == SceneState::Unloaded)
    {
        ImGui::Dummy(progressBarSize);
    }
    else if (scene2->getSceneState() == SceneState::Loading)
	{
		ImGui::ProgressBar(progress2, progressBarSize);
    }
    else if(scene2->getSceneState() == SceneState::Disabled || scene2->getSceneState() == SceneState::Enabled)
    {
        ImGui::PushID("UnloadButton2");
        if (ImGui::ImageButton((void*)(intptr_t)xtexId, xButtonSize, buttonUv0, buttonUv1))
        {
            SceneManager::getInstance().unloadSceneAsync(1);
        }
        ImGui::PopID();
    }
    ImGui::SameLine(0, 32);
    if (scene3->getSceneState() == SceneState::Unloaded)
    {
        ImGui::Dummy(progressBarSize);
    }
    else if (scene3->getSceneState() == SceneState::Loading)
    {
        ImGui::ProgressBar(progress3, progressBarSize);
    }
    else if (scene3->getSceneState() == SceneState::Disabled || scene3->getSceneState() == SceneState::Enabled)
    {
        ImGui::PushID("UnloadButton3");
        if (ImGui::ImageButton((void*)(intptr_t)xtexId, xButtonSize, buttonUv0, buttonUv1))
        {
            SceneManager::getInstance().unloadSceneAsync(2);
        }
        ImGui::PopID();
    }
    ImGui::SameLine(0, 32);
    if (scene4->getSceneState() == SceneState::Unloaded)
    {
        ImGui::Dummy(progressBarSize);
    }
    else if (scene4->getSceneState() == SceneState::Loading)
    {
        ImGui::ProgressBar(progress4, progressBarSize);
    }
    else if (scene4->getSceneState() == SceneState::Disabled || scene4->getSceneState() == SceneState::Enabled)
    {
        ImGui::PushID("UnloadButton4");
        if (ImGui::ImageButton((void*)(intptr_t)xtexId, xButtonSize, buttonUv0, buttonUv1))
        {
            SceneManager::getInstance().unloadSceneAsync(3);
        }
        ImGui::PopID();
    }
    ImGui::SameLine(0, 32);
    if (scene5->getSceneState() == SceneState::Unloaded)
    {
        ImGui::Dummy(progressBarSize);
    }
    else if (scene5->getSceneState() == SceneState::Loading)
    {
        ImGui::ProgressBar(progress5, progressBarSize);
    }
    else if (scene5->getSceneState() == SceneState::Disabled || scene5->getSceneState() == SceneState::Enabled)
    {
        ImGui::PushID("UnloadButton5");
        if (ImGui::ImageButton((void*)(intptr_t)xtexId, xButtonSize, buttonUv0, buttonUv1))
        {
            SceneManager::getInstance().unloadSceneAsync(4);
        }
        ImGui::PopID();
    }
    
    ImGui::End();

    float mainScenePercentLoaded = sceneManager.getMainProgressBarPercent();
    if (mainScenePercentLoaded >= 0.0f)
    {
        ImVec2 glfwWindowSize(glfwWindowSizeX / 2, glfwWindowSizeY / 2);
        ImVec2 loadingBarSize(256.0f, 16.0f);
        ImVec2 loadingBarHalfSize(loadingBarSize.x / 2, loadingBarSize.y / 2);
        ImVec2 loadingBarWindowSize(loadingBarSize.x + 32.0f, loadingBarSize.y + 40.0f);
        ImVec2 loadingBarWindowPos(glfwWindowSize.x - loadingBarHalfSize.x, glfwWindowSize.y - loadingBarHalfSize.y);;
    	
        ImGui::SetNextWindowSize(loadingBarWindowSize);
        ImGui::SetNextWindowPos(loadingBarWindowPos);
    	ImGui::Begin("Loading Bar");
        ImGui::ProgressBar(mainScenePercentLoaded, loadingBarSize);
        ImGui::End();
    }

    ImGui::SetNextWindowSize(ImVec2(128.0f, 64.0f));
    ImGui::SetNextWindowPos(ImVec2(glfwWindowSizeX - 128.0f, glfwWindowSizeY - 64.0f));
    ImGui::Begin("FPS");
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();
}

void processInput(GLFWwindow* window)
{
	// Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
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
    for (Scene* scene : SceneManager::getInstance().getEnabledScenes())
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
    	
        AssetManager::getInstance().instantiateNewLoadedTextures();
        AssetManager::getInstance().instantiateNewLoadedMeshes();
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
