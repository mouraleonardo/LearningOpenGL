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

    //--------------------------------------------------
    // Sprint
    //--------------------------------------------------

    float walkSpeed;

    float sprintSpeed;

    //--------------------------------------------------
    // Physics
    //--------------------------------------------------

    float verticalVelocity;

    float gravity;

    float jumpForce;

    bool grounded;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    float playerRadius;

    float playerHeight;

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
    // View Matrix
    //--------------------------------------------------

    glm::mat4 GetViewMatrix() const;

    //--------------------------------------------------
    // Horizontal Movement
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
    // Physics
    //--------------------------------------------------

    void ApplyGravity(
        float deltaTime);

    void Jump();

    void Land(
        float groundHeight);

    float GetVerticalVelocity() const;

    bool IsGrounded() const;

    //--------------------------------------------------
    // Physics Settings
    //--------------------------------------------------

    void SetGravity(
        float value);

    float GetGravity() const;

    void SetJumpForce(
        float value);

    float GetJumpForce() const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    void SetPlayerRadius(
        float radius);

    float GetPlayerRadius() const;

    void SetPlayerHeight(
        float height);

    float GetPlayerHeight() const;

    //--------------------------------------------------
    // Movement Speed
    //--------------------------------------------------

    void SetMovementSpeed(
        float speed);

    float GetMovementSpeed() const;

    //--------------------------------------------------
    // Sprint
    //--------------------------------------------------

    void SetWalkSpeed(
        float speed);

    float GetWalkSpeed() const;

    void SetSprintSpeed(
        float speed);

    float GetSprintSpeed() const;

    void StartSprint();

    void StopSprint();

    //--------------------------------------------------
    // Mouse Sensitivity
    //--------------------------------------------------

    void SetMouseSensitivity(
        float sensitivity);

    float GetMouseSensitivity() const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Camera();
};

#endif