#include "Door.h"

#include <glm.hpp>

Door::Door()
{
    //--------------------------------------------------
    // Default Position
    //--------------------------------------------------

    position =
    {
        0.0f,
        0.0f,
        0.0f
    };

    //--------------------------------------------------
    // Default Size
    //--------------------------------------------------

    width =
        2.0f;

    height =
        3.0f;

    depth =
        0.5f;

    //--------------------------------------------------
    // State
    //--------------------------------------------------

    open =
        false;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    interactionDistance =
        3.0f;
}

//--------------------------------------------------
// Position
//--------------------------------------------------

void Door::SetPosition(
    const glm::vec3& newPosition)
{
    position =
        newPosition;
}

glm::vec3 Door::GetPosition() const
{
    return position;
}

//--------------------------------------------------
// Size
//--------------------------------------------------

void Door::SetSize(
    float newWidth,
    float newHeight,
    float newDepth)
{
    width =
        newWidth;

    height =
        newHeight;

    depth =
        newDepth;
}

float Door::GetWidth() const
{
    return width;
}

float Door::GetHeight() const
{
    return height;
}

float Door::GetDepth() const
{
    return depth;
}

//--------------------------------------------------
// State
//--------------------------------------------------

void Door::Open()
{
    open =
        true;
}

void Door::Close()
{
    open =
        false;
}

void Door::Toggle()
{
    open =
        !open;
}

bool Door::IsOpen() const
{
    return open;
}

//--------------------------------------------------
// Interaction
//--------------------------------------------------

void Door::SetInteractionDistance(
    float distance)
{
    interactionDistance =
        distance;
}

float Door::GetInteractionDistance() const
{
    return interactionDistance;
}

bool Door::CanInteract(
    const glm::vec3& playerPosition) const
{
    float distance =
        glm::distance(
            playerPosition,
            position);

    return
        distance <=
        interactionDistance;
}

//--------------------------------------------------
// Bounds
//--------------------------------------------------

glm::vec3 Door::GetMinBounds() const
{
    return
    {
        position.x -
        width * 0.5f,

        position.y,

        position.z -
        depth * 0.5f
    };
}

glm::vec3 Door::GetMaxBounds() const
{
    return
    {
        position.x +
        width * 0.5f,

        position.y +
        height,

        position.z +
        depth * 0.5f
    };
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Door::~Door()
{
}