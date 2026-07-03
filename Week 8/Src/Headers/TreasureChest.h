#ifndef TREASURECHEST_H
#define TREASURECHEST_H

#include <glm.hpp>

class TreasureChest
{
private:

    //--------------------------------------------------
    // Transform
    //--------------------------------------------------

    glm::vec3 position;

    float rotation;

    glm::vec3 scale;

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

    bool opened;

    float currentLidAngle;

    float targetLidAngle;

    float animationSpeed;

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    TreasureChest();

    //--------------------------------------------------
    // Position
    //--------------------------------------------------

    void SetPosition(
        const glm::vec3& newPosition);

    glm::vec3 GetPosition() const;

    //--------------------------------------------------
    // Rotation
    //--------------------------------------------------

    void SetRotation(
        float angle);

    float GetRotation() const;

    //--------------------------------------------------
    // Scale
    //--------------------------------------------------

    void SetScale(
        const glm::vec3& newScale);

    glm::vec3 GetScale() const;

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

    bool IsOpened() const;

    //--------------------------------------------------
    // Animation
    //--------------------------------------------------

    void Update(
        float deltaTime);

    float GetCurrentLidAngle() const;

    float GetTargetLidAngle() const;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    void SetInteractionDistance(
        float distance);

    float GetInteractionDistance() const;

    bool CanInteract(
        const glm::vec3& playerPosition) const;

    //--------------------------------------------------
    // Bounds
    //--------------------------------------------------

    glm::vec3 GetMinBounds() const;

    glm::vec3 GetMaxBounds() const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    bool CheckCollision(
        const glm::vec3& playerPosition,
        float playerRadius) const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~TreasureChest();
};

#endif