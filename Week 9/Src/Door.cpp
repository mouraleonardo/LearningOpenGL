#include "Door.h"

#include <glm.hpp>

Door::Door()
{
    //--------------------------------------------------
    // Transform
    //--------------------------------------------------

    position =
    {
        0.0f,
        0.0f,
        0.0f
    };

    //--------------------------------------------------
    // Size
    //--------------------------------------------------

    width =
        4.0f;

    height =
        6.0f;

    depth =
        0.5f;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    interactionDistance =
        5.0f;

    //--------------------------------------------------
    // Animation
    //--------------------------------------------------

    open =
        false;

    currentAngle =
        0.0f;

    targetAngle =
        0.0f;

    animationSpeed =
        120.0f;
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

    targetAngle =
        90.0f;
}

void Door::Close()
{
    open =
        false;

    targetAngle =
        0.0f;
}

void Door::Toggle()
{
    if (open)
    {
        Close();
    }
    else
    {
        Open();
    }
}

bool Door::IsOpen() const
{
    return open;
}

//--------------------------------------------------
// Animation
//--------------------------------------------------

void Door::Update(
    float deltaTime)
{
    float step =
        animationSpeed *
        deltaTime;

    //--------------------------------------------------
    // Opening
    //--------------------------------------------------

    if (
        currentAngle <
        targetAngle)
    {
        currentAngle +=
            step;

        if (
            currentAngle >
            targetAngle)
        {
            currentAngle =
                targetAngle;
        }
    }

    //--------------------------------------------------
    // Closing
    //--------------------------------------------------

    if (
        currentAngle >
        targetAngle)
    {
        currentAngle -=
            step;

        if (
            currentAngle <
            targetAngle)
        {
            currentAngle =
                targetAngle;
        }
    }
}

float Door::GetCurrentAngle() const
{
    return currentAngle;
}

float Door::GetTargetAngle() const
{
    return targetAngle;
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
// Collision
//--------------------------------------------------

bool Door::CheckCollision(
    const glm::vec3& playerPosition,
    float playerRadius) const
{
    //--------------------------------------------------
    // Door mostly open
    //--------------------------------------------------

    if (
        currentAngle >
        70.0f)
    {
        return false;
    }

    glm::vec3 minBounds =
        GetMinBounds();

    glm::vec3 maxBounds =
        GetMaxBounds();

    float closestX =
        glm::clamp(
            playerPosition.x,
            minBounds.x,
            maxBounds.x);

    float closestY =
        glm::clamp(
            playerPosition.y,
            minBounds.y,
            maxBounds.y);

    float closestZ =
        glm::clamp(
            playerPosition.z,
            minBounds.z,
            maxBounds.z);

    float dx =
        playerPosition.x -
        closestX;

    float dy =
        playerPosition.y -
        closestY;

    float dz =
        playerPosition.z -
        closestZ;

    float distanceSquared =
        dx * dx +
        dy * dy +
        dz * dz;

    return
        distanceSquared <
        playerRadius *
        playerRadius;
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