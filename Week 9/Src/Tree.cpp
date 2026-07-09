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
    // Rotation
    //--------------------------------------------------

    rotation =
        0.0f;

    //--------------------------------------------------
    // Scale
    //--------------------------------------------------

    scale =
        1.0f;

    //--------------------------------------------------
    // Tree Type
    //--------------------------------------------------

    treeType =
        0;

    //--------------------------------------------------
    // Trunk
    //--------------------------------------------------

    trunkWidth =
        1.0f;

    trunkHeight =
        4.0f;

    //--------------------------------------------------
    // Leaves
    //--------------------------------------------------

    leavesSize =
        4.0f;
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
// Rotation
//--------------------------------------------------

void Tree::SetRotation(
    float angle)
{
    rotation =
        angle;
}

float Tree::GetRotation() const
{
    return rotation;
}

//--------------------------------------------------
// Scale
//--------------------------------------------------

void Tree::SetScale(
    float newScale)
{
    scale =
        newScale;
}

float Tree::GetScale() const
{
    return scale;
}

//--------------------------------------------------
// Tree Type
//--------------------------------------------------

void Tree::SetTreeType(
    int type)
{
    treeType =
        type;
}

int Tree::GetTreeType() const
{
    return treeType;
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
    return
        trunkWidth *
        scale;
}

float Tree::GetTrunkHeight() const
{
    return
        trunkHeight *
        scale;
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
    return
        leavesSize *
        scale;
}

//--------------------------------------------------
// Bounds
//--------------------------------------------------

glm::vec3 Tree::GetMinBounds() const
{
    float width =
        GetTrunkWidth();

    return
    {
        position.x -
        width * 0.5f,

        position.y,

        position.z -
        width * 0.5f
    };
}

glm::vec3 Tree::GetMaxBounds() const
{
    float width =
        GetTrunkWidth();

    return
    {
        position.x +
        width * 0.5f,

        position.y +
        GetTrunkHeight(),

        position.z +
        width * 0.5f
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

    float closestX =
        glm::clamp(
            point.x,
            minBounds.x,
            maxBounds.x);

    float closestY =
        glm::clamp(
            point.y,
            minBounds.y,
            maxBounds.y);

    float closestZ =
        glm::clamp(
            point.z,
            minBounds.z,
            maxBounds.z);

    float dx =
        point.x -
        closestX;

    float dy =
        point.y -
        closestY;

    float dz =
        point.z -
        closestZ;

    float distanceSquared =
        dx * dx +
        dy * dy +
        dz * dz;

    return
        distanceSquared <
        radius *
        radius;
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Tree::~Tree()
{
}