/*
    ============================================================
    Treasure Chest - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This file implements a simple interactive Treasure Chest
    composed of two cube meshes.

    The chest is divided into two independent parts:

        • Base
        • Lid

    The base remains static while the lid can rotate around
    its rear hinge, allowing the chest to open and close.

    The animation is performed by gradually changing the lid
    rotation angle over time using delta time, producing a
    smooth frame-independent animation.

    Responsibilities:

        • Build the treasure chest
        • Control opening and closing
        • Animate the lid
        • Generate Model Matrices
        • Render both chest parts

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLM
        • C++

    Learning Topics:

        • Model Matrix
        • Object Composition
        • Hierarchical Transformations
        • Matrix Translation
        • Matrix Rotation
        • Matrix Scaling
        • Delta Time Animation
        • Interactive Objects

    ============================================================
*/

#include "TreasureChest.h"

#include <gtc/matrix_transform.hpp>

TreasureChest::TreasureChest()
{
    //----------------------------------------------------------
    // Initial world position.
    //----------------------------------------------------------

    position = glm::vec3(0.0f);

    //----------------------------------------------------------
    // Base dimensions.
    //----------------------------------------------------------

    baseWidth = 2.0f;
    baseHeight = 1.0f;
    baseDepth = 1.0f;

    //----------------------------------------------------------
    // Lid dimensions.
    //----------------------------------------------------------

    lidWidth = 2.0f;
    lidHeight = 0.5f;
    lidDepth = 1.0f;

    //----------------------------------------------------------
    // Animation state.
    //----------------------------------------------------------

    lidAngle = 0.0f;
    opened = false;
}

void TreasureChest::SetPosition(const glm::vec3& pos)
{
    //----------------------------------------------------------
    // Move the entire chest to a new world position.
    //----------------------------------------------------------

    position = pos;
}

void TreasureChest::Toggle()
{
    //----------------------------------------------------------
    // Toggle between opened and closed states.
    //----------------------------------------------------------

    opened = !opened;
}

void TreasureChest::Update(float deltaTime)
{
    //----------------------------------------------------------
    // Animation speed in degrees per second.
    //----------------------------------------------------------

    const float speed = 120.0f;

    //----------------------------------------------------------
    // Open animation.
    //----------------------------------------------------------

    if (opened)
    {
        if (lidAngle < 110.0f)
        {
            lidAngle += speed * deltaTime;

            if (lidAngle > 110.0f)
                lidAngle = 110.0f;
        }
    }
    //----------------------------------------------------------
    // Close animation.
    //----------------------------------------------------------
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
    //----------------------------------------------------------
    // Draw the Base.
    //----------------------------------------------------------

    glm::mat4 model = glm::mat4(1.0f);

    //----------------------------------------------------------
    // Move the base into world space.
    //----------------------------------------------------------

    model = glm::translate(
        model,
        position
    );

    //----------------------------------------------------------
    // Scale the cube into the base dimensions.
    //----------------------------------------------------------

    model = glm::scale(
        model,
        glm::vec3(
            baseWidth,
            baseHeight,
            baseDepth
        )
    );

    //----------------------------------------------------------
    // Send the Model Matrix to the shader.
    //----------------------------------------------------------

    shader.SetMat4("model", model);

    //----------------------------------------------------------
    // Render the base.
    //----------------------------------------------------------

    cube.Draw();

    //----------------------------------------------------------
    // Draw the Lid.
    //----------------------------------------------------------

    model = glm::mat4(1.0f);

    //----------------------------------------------------------
    // Step 1
    //
    // Move the lid to the chest position.
    //----------------------------------------------------------

    model = glm::translate(
        model,
        position
    );

    //----------------------------------------------------------
    // Step 2
    //
    // Move the transformation origin to the hinge located
    // at the back of the chest.
    //----------------------------------------------------------

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            baseHeight * 0.5f,
            -baseDepth * 0.5f
        )
    );

    //----------------------------------------------------------
    // Step 3
    //
    // Rotate the lid around the hinge.
    //----------------------------------------------------------

    model = glm::rotate(
        model,
        glm::radians(-lidAngle),
        glm::vec3(
            1.0f,
            0.0f,
            0.0f
        )
    );

    //----------------------------------------------------------
    // Step 4
    //
    // Move the cube back so its center matches the hinge
    // transformation.
    //----------------------------------------------------------

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            lidHeight * 0.5f,
            baseDepth * 0.5f
        )
    );

    //----------------------------------------------------------
    // Step 5
    //
    // Scale the cube into the lid dimensions.
    //----------------------------------------------------------

    model = glm::scale(
        model,
        glm::vec3(
            lidWidth,
            lidHeight,
            lidDepth
        )
    );

    //----------------------------------------------------------
    // Upload the Model Matrix.
    //----------------------------------------------------------

    shader.SetMat4(
        "model",
        model
    );

    //----------------------------------------------------------
    // Render the lid.
    //----------------------------------------------------------

    cube.Draw();
}