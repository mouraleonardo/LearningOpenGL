#pragma once

#include <glm.hpp>

#include "Mesh.h"
#include "Shader.h"

class TreasureChest
{
public:

    TreasureChest();

    void SetPosition(const glm::vec3& position);

    void Toggle();

    void Update(float deltaTime);

    void Draw(Shader& shader);

private:

    Mesh cube;

    glm::vec3 position;

    float baseWidth;
    float baseHeight;
    float baseDepth;

    float lidWidth;
    float lidHeight;
    float lidDepth;

    float lidAngle;

    bool opened;
};