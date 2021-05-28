#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

// Default camera values
static const float YAW = -90.0f;
static const float PITCH = 0.0f;
static const float SPEED = 50.0f;
static const float SENSITIVITY = 0.1f;
static const float ZOOM = 45.0f;
static const float ASPECT_RATIO = 16.0f / 9.0f;
static const float NEAR_CLIP_PLANE = 0.1f;
static const float FAR_CLIP_PLANE = 10000.0f;

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float AspectRatio;

    Camera(glm::vec3 position = glm::vec3(), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float aspectRatio = ASPECT_RATIO);

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yOffset);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

private:
    void updateCameraVectors();
};
