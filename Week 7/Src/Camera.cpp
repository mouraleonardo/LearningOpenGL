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
        1.8f,
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
    // FPS Rotation
    //--------------------------------------------------

    yaw =
        -90.0f;

    pitch =
        0.0f;

    //--------------------------------------------------
    // Movement
    //--------------------------------------------------

    walkSpeed =
        5.0f;

    sprintSpeed =
        10.0f;

    movementSpeed =
        walkSpeed;

    mouseSensitivity =
        0.1f;

    //--------------------------------------------------
    // Physics
    //--------------------------------------------------

    verticalVelocity =
        0.0f;

    gravity =
        20.0f;

    jumpForce =
        8.0f;

    grounded =
        true;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    playerRadius =
        0.4f;

    playerHeight =
        1.8f;

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
// Direction Vectors
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
// Horizontal Movement
//--------------------------------------------------

void Camera::MoveForward(
    float deltaTime)
{
    glm::vec3 moveDirection =
    {
        front.x,
        0.0f,
        front.z
    };

    moveDirection =
        glm::normalize(
            moveDirection);

    position +=
        moveDirection *
        movementSpeed *
        deltaTime;
}

void Camera::MoveBackward(
    float deltaTime)
{
    glm::vec3 moveDirection =
    {
        front.x,
        0.0f,
        front.z
    };

    moveDirection =
        glm::normalize(
            moveDirection);

    position -=
        moveDirection *
        movementSpeed *
        deltaTime;
}

void Camera::MoveLeft(
    float deltaTime)
{
    glm::vec3 moveDirection =
    {
        right.x,
        0.0f,
        right.z
    };

    moveDirection =
        glm::normalize(
            moveDirection);

    position -=
        moveDirection *
        movementSpeed *
        deltaTime;
}

void Camera::MoveRight(
    float deltaTime)
{
    glm::vec3 moveDirection =
    {
        right.x,
        0.0f,
        right.z
    };

    moveDirection =
        glm::normalize(
            moveDirection);

    position +=
        moveDirection *
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
// Physics
//--------------------------------------------------

void Camera::ApplyGravity(
    float deltaTime)
{
    if (grounded)
    {
        return;
    }

    verticalVelocity -=
        gravity *
        deltaTime;

    position.y +=
        verticalVelocity *
        deltaTime;
}

void Camera::Jump()
{
    if (!grounded)
    {
        return;
    }

    grounded =
        false;

    verticalVelocity =
        jumpForce;
}

void Camera::Land(
    float groundHeight)
{
    position.y =
        groundHeight +
        playerHeight;

    verticalVelocity =
        0.0f;

    grounded =
        true;
}

float Camera::GetVerticalVelocity() const
{
    return verticalVelocity;
}

bool Camera::IsGrounded() const
{
    return grounded;
}

//--------------------------------------------------
// Physics Settings
//--------------------------------------------------

void Camera::SetGravity(
    float value)
{
    gravity =
        value;
}

float Camera::GetGravity() const
{
    return gravity;
}

void Camera::SetJumpForce(
    float value)
{
    jumpForce =
        value;
}

float Camera::GetJumpForce() const
{
    return jumpForce;
}

//--------------------------------------------------
// Collision
//--------------------------------------------------

void Camera::SetPlayerRadius(
    float radius)
{
    playerRadius =
        radius;
}

float Camera::GetPlayerRadius() const
{
    return playerRadius;
}

void Camera::SetPlayerHeight(
    float height)
{
    playerHeight =
        height;
}

float Camera::GetPlayerHeight() const
{
    return playerHeight;
}

//--------------------------------------------------
// Speed
//--------------------------------------------------

void Camera::SetMovementSpeed(
    float speed)
{
    movementSpeed =
        speed;

    walkSpeed =
        speed;
}

float Camera::GetMovementSpeed() const
{
    return movementSpeed;
}

//--------------------------------------------------
// Sprint
//--------------------------------------------------

void Camera::SetWalkSpeed(
    float speed)
{
    walkSpeed =
        speed;

    movementSpeed =
        speed;
}

float Camera::GetWalkSpeed() const
{
    return walkSpeed;
}

void Camera::SetSprintSpeed(
    float speed)
{
    sprintSpeed =
        speed;
}

float Camera::GetSprintSpeed() const
{
    return sprintSpeed;
}

void Camera::StartSprint()
{
    movementSpeed =
        sprintSpeed;
}

void Camera::StopSprint()
{
    movementSpeed =
        walkSpeed;
}

//--------------------------------------------------
// Mouse Sensitivity
//--------------------------------------------------

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
            glm::radians(
                yaw))
        *
        std::cos(
            glm::radians(
                pitch));

    direction.y =
        std::sin(
            glm::radians(
                pitch));

    direction.z =
        std::sin(
            glm::radians(
                yaw))
        *
        std::cos(
            glm::radians(
                pitch));

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