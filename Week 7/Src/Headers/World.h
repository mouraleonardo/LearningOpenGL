#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <glm.hpp>

#include "Tree.h"
#include "Door.h"

class World
{
private:

    //--------------------------------------------------
    // Terrain
    //--------------------------------------------------

    float terrainWidth;

    float terrainDepth;

    //--------------------------------------------------
    // Trees
    //--------------------------------------------------

    std::vector<Tree> trees;

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    Door door;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    float playerRadius;

private:

    //--------------------------------------------------
    // Generation
    //--------------------------------------------------

    void GenerateTrees();

    void GenerateDoor();

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    World();

    //--------------------------------------------------
    // Initialization
    //--------------------------------------------------

    void Generate();

    void Clear();

    //--------------------------------------------------
    // Terrain
    //--------------------------------------------------

    void SetTerrainSize(
        float width,
        float depth);

    float GetTerrainWidth() const;

    float GetTerrainDepth() const;

    //--------------------------------------------------
    // Trees
    //--------------------------------------------------

    std::vector<Tree>&
        GetTrees();

    const std::vector<Tree>&
        GetTrees() const;

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    Door& GetDoor();

    const Door& GetDoor() const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    void SetPlayerRadius(
        float radius);

    float GetPlayerRadius() const;

    bool CheckTreeCollision(
        const glm::vec3& position) const;

    bool CheckWorldBounds(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    bool CanInteractWithDoor(
        const glm::vec3& playerPosition) const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~World();
};

#endif