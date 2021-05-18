#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float aspectRatio)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;
	AspectRatio = aspectRatio;
	updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;

	if (direction == CameraMovement::FORWARD)
	{
		Position += Front * velocity;
	}
	if (direction == CameraMovement::BACKWARD)
	{
		Position -= Front * velocity;
	}
	if (direction == CameraMovement::LEFT)
	{
		Position -= Right * velocity;
	}
	if (direction == CameraMovement::RIGHT)
	{
		Position += Right * velocity;
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
	Zoom -= yOffset;
	if (Zoom < 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom > 45.0f)
	{
		Zoom = 45.0f;
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 front
	{
		cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
		sin(glm::radians(Pitch)),
		sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
	};
	
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(Zoom), AspectRatio, NEAR_CLIP_PLANE, FAR_CLIP_PLANE);
}
