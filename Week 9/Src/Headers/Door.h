#ifndef DOOR_H
#define DOOR_H

#include <glm.hpp>

class Door
{
private:

    //--------------------------------------------------
    // Transform
    //--------------------------------------------------

    glm::vec3 position;

    //--------------------------------------------------
    // Size
    //--------------------------------------------------

    float width;

    float height;

    float depth;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    float interactionDistance;

    //--------------------------------------------------
    // Animation
    //--------------------------------------------------

    bool open;

    float currentAngle;

    float targetAngle;

    float animationSpeed;

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    Door();

    //--------------------------------------------------
    // Position
    //--------------------------------------------------

    void SetPosition(
        const glm::vec3& newPosition);

    glm::vec3 GetPosition() const;

    //--------------------------------------------------
    // Size
    //--------------------------------------------------

    void SetSize(
        float newWidth,
        float newHeight,
        float newDepth);

    float GetWidth() const;

    float GetHeight() const;

    float GetDepth() const;

    //--------------------------------------------------
    // State
    //--------------------------------------------------

    void Open();

    void Close();

    void Toggle();

    bool IsOpen() const;

    //--------------------------------------------------
    // Animation
    //--------------------------------------------------

    void Update(
        float deltaTime);

    float GetCurrentAngle() const;

    float GetTargetAngle() const;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    void SetInteractionDistance(
        float distance);

    float GetInteractionDistance() const;

    bool CanInteract(
        const glm::vec3& playerPosition) const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    bool CheckCollision(
        const glm::vec3& playerPosition,
        float playerRadius) const;

    //--------------------------------------------------
    // Bounds
    //--------------------------------------------------

    glm::vec3 GetMinBounds() const;

    glm::vec3 GetMaxBounds() const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Door();
};

#endif