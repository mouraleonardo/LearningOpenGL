#include "TreasureChest.h"

#include <gtc/matrix_transform.hpp>

TreasureChest::TreasureChest()
{
    position = glm::vec3(0.0f);

    baseWidth = 2.0f;
    baseHeight = 1.0f;
    baseDepth = 1.0f;

    lidWidth = 2.0f;
    lidHeight = 0.5f;
    lidDepth = 1.0f;

    lidAngle = 0.0f;
    opened = false;
}

void TreasureChest::SetPosition(const glm::vec3& pos)
{
    position = pos;
}

void TreasureChest::Toggle()
{
    opened = !opened;
}

void TreasureChest::Update(float deltaTime)
{
    const float speed = 120.0f;

    if (opened)
    {
        if (lidAngle < 110.0f)
        {
            lidAngle += speed * deltaTime;

            if (lidAngle > 110.0f)
                lidAngle = 110.0f;
        }
    }
    else
    {
        if (lidAngle > 0.0f)
        {
            lidAngle -= speed * deltaTime;

            if (lidAngle < 0.0f)
                lidAngle = 0.0f;
        }
    }
}

void TreasureChest::Draw(Shader& shader)
{
    //-----------------------------------------------------
    // BASE
    //-----------------------------------------------------

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        position
    );

    model = glm::scale(
        model,
        glm::vec3(
            baseWidth,
            baseHeight,
            baseDepth
        )
    );

    shader.SetMat4("model", model);

    cube.Draw();

    //-----------------------------------------------------
    // TAMPA
    //-----------------------------------------------------

    model = glm::mat4(1.0f);

    //
    // Centro do baú
    //
    model = glm::translate(
        model,
        position
    );

    //
    // Vai até a dobradiça
    //
    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            baseHeight * 0.5f,
            -baseDepth * 0.5f
        )
    );

    //
    // Rotação
    //
    model = glm::rotate(
        model,
        glm::radians(-lidAngle),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    //
    // Volta ao centro da tampa
    //
    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            lidHeight * 0.5f,
            baseDepth * 0.5f
        )
    );

    //
    // Escala
    //
    model = glm::scale(
        model,
        glm::vec3(
            lidWidth,
            lidHeight,
            lidDepth
        )
    );

    shader.SetMat4("model", model);

    cube.Draw();
}