#include "Tree.h"

#include <glm.hpp>

Tree::Tree()
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
    // Trunk
    //--------------------------------------------------

    trunkWidth =
        0.8f;

    trunkHeight =
        2.0f;

    //--------------------------------------------------
    // Leaves
    //--------------------------------------------------

    leavesSize =
        2.0f;
}

//--------------------------------------------------
// Position
//--------------------------------------------------

void Tree::SetPosition(
    const glm::vec3& newPosition)
{
    position =
        newPosition;
}

glm::vec3 Tree::GetPosition() const
{
    return position;
}

//--------------------------------------------------
// Trunk
//--------------------------------------------------

void Tree::SetTrunkSize(
    float width,
    float height)
{
    trunkWidth =
        width;

    trunkHeight =
        height;
}

float Tree::GetTrunkWidth() const
{
    return trunkWidth;
}

float Tree::GetTrunkHeight() const
{
    return trunkHeight;
}

//--------------------------------------------------
// Leaves
//--------------------------------------------------

void Tree::SetLeavesSize(
    float size)
{
    leavesSize =
        size;
}

float Tree::GetLeavesSize() const
{
    return leavesSize;
}

//--------------------------------------------------
// Bounds
//--------------------------------------------------

glm::vec3 Tree::GetMinBounds() const
{
    return
    {
        position.x -
        trunkWidth * 0.5f,

        position.y,

        position.z -
        trunkWidth * 0.5f
    };
}

glm::vec3 Tree::GetMaxBounds() const
{
    return
    {
        position.x +
        trunkWidth * 0.5f,

        position.y +
        trunkHeight,

        position.z +
        trunkWidth * 0.5f
    };
}

//--------------------------------------------------
// Collision
//--------------------------------------------------

bool Tree::CheckCollision(
    const glm::vec3& point,
    float radius) const
{
    glm::vec3 minBounds =
        GetMinBounds();

    glm::vec3 maxBounds =
        GetMaxBounds();

    if (
        point.x + radius <
        minBounds.x)
    {
        return false;
    }

    if (
        point.x - radius >
        maxBounds.x)
    {
        return false;
    }

    if (
        point.z + radius <
        minBounds.z)
    {
        return false;
    }

    if (
        point.z - radius >
        maxBounds.z)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Tree::~Tree()
{
}