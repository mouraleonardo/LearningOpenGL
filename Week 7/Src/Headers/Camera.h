#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
private:

    //--------------------------------------------------
    // Transform
    //--------------------------------------------------

    glm::vec3 position;

    glm::vec3 front;

    glm::vec3 up;

    glm::vec3 right;

    glm::vec3 worldUp;

    //--------------------------------------------------
    // Rotation
    //--------------------------------------------------

    float yaw;

    float pitch;

    //--------------------------------------------------
    // Movement
    //--------------------------------------------------

    float movementSpeed;

    float mouseSensitivity;

private:

    //--------------------------------------------------
    // Internal
    //--------------------------------------------------

    void UpdateVectors();

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    Camera();

    //--------------------------------------------------
    // Position
    //--------------------------------------------------

    void SetPosition(
        const glm::vec3& newPosition);

    glm::vec3 GetPosition() const;

    //--------------------------------------------------
    // Rotation
    //--------------------------------------------------

    void SetYaw(
        float value);

    float GetYaw() const;

    void SetPitch(
        float value);

    float GetPitch() const;

    //--------------------------------------------------
    // Vectors
    //--------------------------------------------------

    glm::vec3 GetFront() const;

    glm::vec3 GetRight() const;

    glm::vec3 GetUp() const;

    //--------------------------------------------------
    // Camera Matrix
    //--------------------------------------------------

    glm::mat4 GetViewMatrix() const;

    //--------------------------------------------------
    // Movement
    //--------------------------------------------------

    void MoveForward(
        float deltaTime);

    void MoveBackward(
        float deltaTime);

    void MoveLeft(
        float deltaTime);

    void MoveRight(
        float deltaTime);

    //--------------------------------------------------
    // Mouse
    //--------------------------------------------------

    void ProcessMouseMovement(
        float xOffset,
        float yOffset);

    //--------------------------------------------------
    // Speed
    //--------------------------------------------------

    void SetMovementSpeed(
        float speed);

    float GetMovementSpeed() const;

    void SetMouseSensitivity(
        float sensitivity);

    float GetMouseSensitivity() const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Camera();
};

#endif