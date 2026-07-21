/*
    ============================================================
    FPS Camera - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This file implements a simple First-Person Camera (FPS)
    commonly used in 3D applications and games.

    The camera is responsible for generating the View Matrix
    used by the rendering pipeline and processing user input
    for movement and orientation.

    The implementation supports:

        • Forward and backward movement
        • Left and right strafing
        • Mouse Look
        • Zoom using the mouse wheel
        • Smooth movement using delta time
        • Euler Angle rotations (Yaw and Pitch)

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLM
        • C++

    Learning Topics:

        • Camera Systems
        • View Matrix
        • Euler Angles
        • Vector Mathematics
        • Cross Product
        • Normalization
        • FPS Navigation
        • Delta Time Movement

    ============================================================
*/

#include "Camera.h"

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch)
{
    //---------------------------------------------------------
    // Store the initial camera position.
    //---------------------------------------------------------

    Position = position;

    //---------------------------------------------------------
    // Store the world's up direction.
    //---------------------------------------------------------

    WorldUp = up;

    //---------------------------------------------------------
    // Initialize camera rotation.
    //---------------------------------------------------------

    Yaw = yaw;
    Pitch = pitch;

    //---------------------------------------------------------
    // The camera initially looks toward the negative Z axis.
    //---------------------------------------------------------

    Front = glm::vec3(
        0.0f,
        0.0f,
        -1.0f
    );

    //---------------------------------------------------------
    // Camera movement configuration.
    //---------------------------------------------------------

    MovementSpeed = 5.0f;

    MouseSensitivity = 0.1f;

    Zoom = 45.0f;

    //---------------------------------------------------------
    // Calculate the initial camera vectors.
    //---------------------------------------------------------

    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    //---------------------------------------------------------
    // Create the View Matrix using the camera position,
    // viewing direction and up vector.
    //---------------------------------------------------------

    return glm::lookAt(
        Position,
        Position + Front,
        Up
    );
}

void Camera::ProcessKeyboard(
    CameraMovement direction,
    float deltaTime)
{
    //---------------------------------------------------------
    // Movement speed must be multiplied by delta time
    // so the camera moves consistently regardless of FPS.
    //---------------------------------------------------------

    float velocity = MovementSpeed * deltaTime;

    //---------------------------------------------------------
    // Move forward.
    //---------------------------------------------------------

    if (direction == FORWARD)
        Position += Front * velocity;

    //---------------------------------------------------------
    // Move backward.
    //---------------------------------------------------------

    if (direction == BACKWARD)
        Position -= Front * velocity;

    //---------------------------------------------------------
    // Strafe left.
    //---------------------------------------------------------

    if (direction == LEFT)
        Position -= Right * velocity;

    //---------------------------------------------------------
    // Strafe right.
    //---------------------------------------------------------

    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(
    float xoffset,
    float yoffset)
{
    //---------------------------------------------------------
    // Apply mouse sensitivity.
    //---------------------------------------------------------

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    //---------------------------------------------------------
    // Update Euler angles.
    //---------------------------------------------------------

    Yaw += xoffset;
    Pitch += yoffset;

    //---------------------------------------------------------
    // Clamp the pitch to avoid gimbal lock.
    //---------------------------------------------------------

    if (Pitch > 89.0f)
        Pitch = 89.0f;

    if (Pitch < -89.0f)
        Pitch = -89.0f;

    //---------------------------------------------------------
    // Recalculate the camera vectors.
    //---------------------------------------------------------

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    //---------------------------------------------------------
    // Modify the field of view (Zoom).
    //---------------------------------------------------------

    Zoom -= yoffset;

    //---------------------------------------------------------
    // Clamp the zoom value.
    //---------------------------------------------------------

    if (Zoom < 1.0f)
        Zoom = 1.0f;

    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    //---------------------------------------------------------
    // Convert Euler angles into a direction vector.
    //---------------------------------------------------------

    glm::vec3 front;

    front.x =
        cos(glm::radians(Yaw)) *
        cos(glm::radians(Pitch));

    front.y =
        sin(glm::radians(Pitch));

    front.z =
        sin(glm::radians(Yaw)) *
        cos(glm::radians(Pitch));

    //---------------------------------------------------------
    // Normalize the front vector.
    //---------------------------------------------------------

    Front = glm::normalize(front);

    //---------------------------------------------------------
    // Calculate the camera's right vector.
    //---------------------------------------------------------

    Right = glm::normalize(
        glm::cross(
            Front,
            WorldUp
        )
    );

    //---------------------------------------------------------
    // Calculate the camera's up vector.
    //---------------------------------------------------------

    Up = glm::normalize(
        glm::cross(
            Right,
            Front
        )
    );
}