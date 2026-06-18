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
    // State
    //--------------------------------------------------

    bool open;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    float interactionDistance;

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
    // Destructor
    //--------------------------------------------------

    ~Door();
};

#endif