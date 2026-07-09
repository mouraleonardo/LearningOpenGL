#include "TreasureChest.h"

#include <glm.hpp>

TreasureChest::TreasureChest()
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

    rotation =
        0.0f;

    scale =
    {
        1.0f,
        1.0f,
        1.0f
    };

    //--------------------------------------------------
    // Size
    //--------------------------------------------------

    width =
        3.0f;

    height =
        2.0f;

    depth =
        2.0f;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    interactionDistance =
        4.0f;

    //--------------------------------------------------
    // Animation
    //--------------------------------------------------

    opened =
        false;

    currentLidAngle =
        0.0f;

    targetLidAngle =
        0.0f;

    animationSpeed =
        120.0f;
}

//--------------------------------------------------
// Position
//--------------------------------------------------

void TreasureChest::SetPosition(
    const glm::vec3& newPosition)
{
    position =
        newPosition;
}

glm::vec3 TreasureChest::GetPosition() const
{
    return position;
}

//--------------------------------------------------
// Rotation
//--------------------------------------------------

void TreasureChest::SetRotation(
    float angle)
{
    rotation =
        angle;
}

float TreasureChest::GetRotation() const
{
    return rotation;
}

//--------------------------------------------------
// Scale
//--------------------------------------------------

void TreasureChest::SetScale(
    const glm::vec3& newScale)
{
    scale =
        newScale;
}

glm::vec3 TreasureChest::GetScale() const
{
    return scale;
}

//--------------------------------------------------
// Size
//--------------------------------------------------

void TreasureChest::SetSize(
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

float TreasureChest::GetWidth() const
{
    return
        width *
        scale.x;
}

float TreasureChest::GetHeight() const
{
    return
        height *
        scale.y;
}

float TreasureChest::GetDepth() const
{
    return
        depth *
        scale.z;
}

//--------------------------------------------------
// State
//--------------------------------------------------

void TreasureChest::Open()
{
    opened =
        true;

    targetLidAngle =
        110.0f;
}

void TreasureChest::Close()
{
    opened =
        false;

    targetLidAngle =
        0.0f;
}

void TreasureChest::Toggle()
{
    if (opened)
    {
        Close();
    }
    else
    {
        Open();
    }
}

bool TreasureChest::IsOpened() const
{
    return opened;
}

//--------------------------------------------------
// Animation
//--------------------------------------------------

void TreasureChest::Update(
    float deltaTime)
{
    float step =
        animationSpeed *
        deltaTime;

    if (
        currentLidAngle <
        targetLidAngle)
    {
        currentLidAngle +=
            step;

        if (
            currentLidAngle >
            targetLidAngle)
        {
            currentLidAngle =
                targetLidAngle;
        }
    }

    if (
        currentLidAngle >
        targetLidAngle)
    {
        currentLidAngle -=
            step;

        if (
            currentLidAngle <
            targetLidAngle)
        {
            currentLidAngle =
                targetLidAngle;
        }
    }
}

float TreasureChest::GetCurrentLidAngle() const
{
    return currentLidAngle;
}

float TreasureChest::GetTargetLidAngle() const
{
    return targetLidAngle;
}

//--------------------------------------------------
// Interaction
//--------------------------------------------------

void TreasureChest::SetInteractionDistance(
    float distance)
{
    interactionDistance =
        distance;
}

float TreasureChest::GetInteractionDistance() const
{
    return interactionDistance;
}

bool TreasureChest::CanInteract(
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

glm::vec3 TreasureChest::GetMinBounds() const
{
    return
    {
        position.x -
        GetWidth() * 0.5f,

        position.y,

        position.z -
        GetDepth() * 0.5f
    };
}

glm::vec3 TreasureChest::GetMaxBounds() const
{
    return
    {
        position.x +
        GetWidth() * 0.5f,

        position.y +
        GetHeight(),

        position.z +
        GetDepth() * 0.5f
    };
}

//--------------------------------------------------
// Collision
//--------------------------------------------------

bool TreasureChest::CheckCollision(
    const glm::vec3& playerPosition,
    float playerRadius) const
{
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
// Destructor
//--------------------------------------------------

TreasureChest::~TreasureChest()
{
}