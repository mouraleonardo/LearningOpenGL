#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <glm.hpp>

#include "Tree.h"
#include "Door.h"
#include "TreasureChest.h"

class World
{
private:

    //--------------------------------------------------
    // Terrain
    //--------------------------------------------------

    float terrainSize;

    //--------------------------------------------------
    // Trees
    //--------------------------------------------------

    std::vector<Tree> trees;

    //--------------------------------------------------
    // Castle
    //--------------------------------------------------

    glm::vec3 castlePosition;

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    Door door;

    //--------------------------------------------------
    // Treasure Chest
    //--------------------------------------------------

    std::vector<TreasureChest> treasureChests;

    //--------------------------------------------------
    // Player Collision
    //--------------------------------------------------

    float playerRadius;

private:

    //--------------------------------------------------
    // Generation
    //--------------------------------------------------

    void GenerateTrees();

    void GenerateCastle();

    void GenerateTreasureChests();

    //--------------------------------------------------
    // Castle Collision
    //--------------------------------------------------

    bool CheckCastleCollision(
        const glm::vec3& position) const;

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    World();

    //--------------------------------------------------
    // Generation
    //--------------------------------------------------

    void Generate();

    void Clear();

    //--------------------------------------------------
    // Terrain
    //--------------------------------------------------

    void SetTerrainSize(
        float size);

    float GetTerrainSize() const;

    //--------------------------------------------------
    // Terrain Height
    //--------------------------------------------------

    float GetHeightAt(
        float x,
        float z) const;

    //--------------------------------------------------
    // Trees
    //--------------------------------------------------

    std::vector<Tree>& GetTrees();

    const std::vector<Tree>& GetTrees() const;

    //--------------------------------------------------
    // Castle
    //--------------------------------------------------

    glm::vec3 GetCastlePosition() const;

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    Door& GetDoor();

    const Door& GetDoor() const;

    //--------------------------------------------------
    // Treasure Chests
    //--------------------------------------------------

    std::vector<TreasureChest>& GetTreasureChests();

    const std::vector<TreasureChest>& GetTreasureChests() const;

    //--------------------------------------------------
    // Player Collision
    //--------------------------------------------------

    void SetPlayerRadius(
        float radius);

    float GetPlayerRadius() const;

    //--------------------------------------------------
    // Tree Collision
    //--------------------------------------------------

    bool CheckTreeCollision(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Door Collision
    //--------------------------------------------------

    bool CheckDoorCollision(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Treasure Chest Collision
    //--------------------------------------------------

    bool CheckTreasureChestCollision(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Castle Collision
    //--------------------------------------------------

    bool IsInsideCastle(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    bool CheckCollision(
        const glm::vec3& position) const;

    //--------------------------------------------------
    // Ground
    //--------------------------------------------------

    bool IsBelowGround(
        const glm::vec3& position,
        float playerHeight) const;

    //--------------------------------------------------
    // Interaction
    //--------------------------------------------------

    bool CanInteractWithDoor(
        const glm::vec3& playerPosition) const;

    //--------------------------------------------------
    // Treasure Chest Interaction
    //--------------------------------------------------

    TreasureChest* GetInteractableTreasureChest(
        const glm::vec3& playerPosition);

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~World();
};

#endif