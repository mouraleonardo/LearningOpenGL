#include "Camera.h"

#include <cmath>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

Camera::Camera()
{
    //--------------------------------------------------
    // Initial Position
    //--------------------------------------------------

    position =
    {
        0.0f,
        2.0f,
        5.0f
    };

    //--------------------------------------------------
    // World Orientation
    //--------------------------------------------------

    worldUp =
    {
        0.0f,
        1.0f,
        0.0f
    };

    //--------------------------------------------------
    // FPS Camera Angles
    //--------------------------------------------------

    yaw =
        -90.0f;

    pitch =
        0.0f;

    //--------------------------------------------------
    // Movement
    //--------------------------------------------------

    movementSpeed =
        5.0f;

    mouseSensitivity =
        0.1f;

    //--------------------------------------------------
    // Initial Vectors
    //--------------------------------------------------

    UpdateVectors();
}

//--------------------------------------------------
// Position
//--------------------------------------------------

void Camera::SetPosition(
    const glm::vec3& newPosition)
{
    position =
        newPosition;
}

glm::vec3 Camera::GetPosition() const
{
    return position;
}

//--------------------------------------------------
// Rotation
//--------------------------------------------------

void Camera::SetYaw(
    float value)
{
    yaw =
        value;

    UpdateVectors();
}

float Camera::GetYaw() const
{
    return yaw;
}

void Camera::SetPitch(
    float value)
{
    pitch =
        value;

    //--------------------------------------------------
    // Clamp Pitch
    //--------------------------------------------------

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    UpdateVectors();
}

float Camera::GetPitch() const
{
    return pitch;
}

//--------------------------------------------------
// Vectors
//--------------------------------------------------

glm::vec3 Camera::GetFront() const
{
    return front;
}

glm::vec3 Camera::GetRight() const
{
    return right;
}

glm::vec3 Camera::GetUp() const
{
    return up;
}

//--------------------------------------------------
// View Matrix
//--------------------------------------------------

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(
        position,
        position + front,
        up);
}

//--------------------------------------------------
// Movement
//--------------------------------------------------

void Camera::MoveForward(
    float deltaTime)
{
    position +=
        front *
        movementSpeed *
        deltaTime;
}

void Camera::MoveBackward(
    float deltaTime)
{
    position -=
        front *
        movementSpeed *
        deltaTime;
}

void Camera::MoveLeft(
    float deltaTime)
{
    position -=
        right *
        movementSpeed *
        deltaTime;
}

void Camera::MoveRight(
    float deltaTime)
{
    position +=
        right *
        movementSpeed *
        deltaTime;
}

//--------------------------------------------------
// Mouse
//--------------------------------------------------

void Camera::ProcessMouseMovement(
    float xOffset,
    float yOffset)
{
    xOffset *=
        mouseSensitivity;

    yOffset *=
        mouseSensitivity;

    yaw +=
        xOffset;

    pitch +=
        yOffset;

    //--------------------------------------------------
    // Clamp Vertical Rotation
    //--------------------------------------------------

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    UpdateVectors();
}

//--------------------------------------------------
// Speed
//--------------------------------------------------

void Camera::SetMovementSpeed(
    float speed)
{
    movementSpeed =
        speed;
}

float Camera::GetMovementSpeed() const
{
    return movementSpeed;
}

void Camera::SetMouseSensitivity(
    float sensitivity)
{
    mouseSensitivity =
        sensitivity;
}

float Camera::GetMouseSensitivity() const
{
    return mouseSensitivity;
}

//--------------------------------------------------
// Internal
//--------------------------------------------------

void Camera::UpdateVectors()
{
    glm::vec3 direction;

    direction.x =
        std::cos(
            glm::radians(yaw))
        *
        std::cos(
            glm::radians(pitch));

    direction.y =
        std::sin(
            glm::radians(pitch));

    direction.z =
        std::sin(
            glm::radians(yaw))
        *
        std::cos(
            glm::radians(pitch));

    front =
        glm::normalize(
            direction);

    right =
        glm::normalize(
            glm::cross(
                front,
                worldUp));

    up =
        glm::normalize(
            glm::cross(
                right,
                front));
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Camera::~Camera()
{
}