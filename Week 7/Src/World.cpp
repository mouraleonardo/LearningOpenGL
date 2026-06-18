#include "World.h"

#include <cstdlib>
#include <ctime>

#include <glm.hpp>

World::World()
{
    //--------------------------------------------------
    // Terrain
    //--------------------------------------------------

    terrainWidth =
        50.0f;

    terrainDepth =
        50.0f;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    playerRadius =
        0.5f;

    //--------------------------------------------------
    // Random Seed
    //--------------------------------------------------

    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)));
}

//--------------------------------------------------
// Generation
//--------------------------------------------------

void World::Generate()
{
    Clear();

    GenerateTrees();

    GenerateDoor();
}

void World::Clear()
{
    trees.clear();
}

//--------------------------------------------------
// Terrain
//--------------------------------------------------

void World::SetTerrainSize(
    float width,
    float depth)
{
    terrainWidth =
        width;

    terrainDepth =
        depth;
}

float World::GetTerrainWidth() const
{
    return terrainWidth;
}

float World::GetTerrainDepth() const
{
    return terrainDepth;
}

//--------------------------------------------------
// Trees
//--------------------------------------------------

std::vector<Tree>&
World::GetTrees()
{
    return trees;
}

const std::vector<Tree>&
World::GetTrees() const
{
    return trees;
}

//--------------------------------------------------
// Door
//--------------------------------------------------

Door& World::GetDoor()
{
    return door;
}

const Door& World::GetDoor() const
{
    return door;
}

//--------------------------------------------------
// Collision
//--------------------------------------------------

void World::SetPlayerRadius(
    float radius)
{
    playerRadius =
        radius;
}

float World::GetPlayerRadius() const
{
    return playerRadius;
}

bool World::CheckTreeCollision(
    const glm::vec3& position) const
{
    for (const Tree& tree : trees)
    {
        if (
            tree.CheckCollision(
                position,
                playerRadius))
        {
            return true;
        }
    }

    return false;
}

bool World::CheckWorldBounds(
    const glm::vec3& position) const
{
    float halfWidth =
        terrainWidth * 0.5f;

    float halfDepth =
        terrainDepth * 0.5f;

    if (
        position.x <
        -halfWidth)
    {
        return false;
    }

    if (
        position.x >
        halfWidth)
    {
        return false;
    }

    if (
        position.z <
        -halfDepth)
    {
        return false;
    }

    if (
        position.z >
        halfDepth)
    {
        return false;
    }

    return true;
}

//--------------------------------------------------
// Interaction
//--------------------------------------------------

bool World::CanInteractWithDoor(
    const glm::vec3& playerPosition) const
{
    return
        door.CanInteract(
            playerPosition);
}

//--------------------------------------------------
// Tree Generation
//--------------------------------------------------

void World::GenerateTrees()
{
    //--------------------------------------------------
    // Generate 20 Trees
    //--------------------------------------------------

    for (int i = 0;
        i < 20;
        i++)
    {
        Tree tree;

        float x =
            static_cast<float>(
                (std::rand() % 400) - 200)
            / 10.0f;

        float z =
            static_cast<float>(
                (std::rand() % 400) - 200)
            / 10.0f;

        //--------------------------------------------------
        // Keep Center Area Clear
        //--------------------------------------------------

        if (
            x > -5.0f &&
            x < 5.0f &&
            z > -5.0f &&
            z < 5.0f)
        {
            i--;
            continue;
        }

        tree.SetPosition(
            {
                x,
                0.0f,
                z
            });

        trees.push_back(
            tree);
    }
}

//--------------------------------------------------
// Door Generation
//--------------------------------------------------

void World::GenerateDoor()
{
    //--------------------------------------------------
    // Wall Between Areas
    //--------------------------------------------------

    door.SetPosition(
        {
            0.0f,
            0.0f,
            15.0f
        });

    door.SetSize(
        3.0f,
        4.0f,
        0.5f);

    door.Close();
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

World::~World()
{
}