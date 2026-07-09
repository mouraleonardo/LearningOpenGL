#ifndef TREE_H
#define TREE_H

#include <glm.hpp>

class Tree
{
private:

    //--------------------------------------------------
    // Transform
    //--------------------------------------------------

    glm::vec3 position;

    float rotation;

    float scale;

    //--------------------------------------------------
    // Tree Type
    //--------------------------------------------------

    int treeType;

    //--------------------------------------------------
    // Trunk
    //--------------------------------------------------

    float trunkWidth;

    float trunkHeight;

    //--------------------------------------------------
    // Leaves
    //--------------------------------------------------

    float leavesSize;

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    Tree();

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
        float newScale);

    float GetScale() const;

    //--------------------------------------------------
    // Tree Type
    //--------------------------------------------------

    void SetTreeType(
        int type);

    int GetTreeType() const;

    //--------------------------------------------------
    // Trunk
    //--------------------------------------------------

    void SetTrunkSize(
        float width,
        float height);

    float GetTrunkWidth() const;

    float GetTrunkHeight() const;

    //--------------------------------------------------
    // Leaves
    //--------------------------------------------------

    void SetLeavesSize(
        float size);

    float GetLeavesSize() const;

    //--------------------------------------------------
    // Bounds
    //--------------------------------------------------

    glm::vec3 GetMinBounds() const;

    glm::vec3 GetMaxBounds() const;

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    bool CheckCollision(
        const glm::vec3& point,
        float radius) const;

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Tree();
};

#endif