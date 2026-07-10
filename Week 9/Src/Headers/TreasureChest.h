/*
    ============================================================
    Treasure Chest - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This class represents a simple interactive Treasure Chest
    composed of two independent cube meshes.

    The object is divided into two main components:

        • Base
        • Lid

    The base remains fixed while the lid can be animated by
    rotating around its rear hinge, simulating the opening
    and closing of a real treasure chest.

    The class also stores the chest dimensions, world position,
    animation state, and provides methods for updating and
    rendering the object.

    Responsibilities:

        • Store the treasure chest state
        • Control lid animation
        • Update animation over time
        • Generate Model Matrices
        • Render the complete object

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLM
        • C++

    Learning Topics:

        • Object-Oriented Design
        • Hierarchical Objects
        • Model Transformations
        • Animation Systems
        • Delta Time
        • Composition
        • Interactive Objects

    ============================================================
*/

#pragma once

#include <glm.hpp>

#include "Mesh.h"
#include "Shader.h"

class TreasureChest
{
public:

    //----------------------------------------------------------
    // Constructor.
    //
    // Initializes the treasure chest dimensions,
    // animation state and default position.
    //----------------------------------------------------------
    TreasureChest();

    //----------------------------------------------------------
    // Sets the world position of the entire treasure chest.
    //----------------------------------------------------------
    void SetPosition(const glm::vec3& position);

    //----------------------------------------------------------
    // Toggles the chest state.
    //
    // If the chest is closed it will start opening.
    // If it is open it will start closing.
    //----------------------------------------------------------
    void Toggle();

    //----------------------------------------------------------
    // Updates the lid animation.
    //
    // The animation uses delta time to ensure smooth and
    // frame-independent motion.
    //----------------------------------------------------------
    void Update(float deltaTime);

    //----------------------------------------------------------
    // Renders the treasure chest.
    //
    // Both the base and lid are rendered using the same cube
    // mesh with different transformations.
    //----------------------------------------------------------
    void Draw(Shader& shader);

private:

    //----------------------------------------------------------
    // Shared cube mesh.
    //
    // The entire treasure chest is built by drawing this mesh
    // multiple times with different transformations.
    //----------------------------------------------------------
    Mesh cube;

    //----------------------------------------------------------
    // World position of the treasure chest.
    //----------------------------------------------------------
    glm::vec3 position;

    //----------------------------------------------------------
    // Base dimensions.
    //----------------------------------------------------------
    float baseWidth;
    float baseHeight;
    float baseDepth;

    //----------------------------------------------------------
    // Lid dimensions.
    //----------------------------------------------------------
    float lidWidth;
    float lidHeight;
    float lidDepth;

    //----------------------------------------------------------
    // Current lid rotation angle.
    //
    // Measured in degrees.
    //----------------------------------------------------------
    float lidAngle;

    //----------------------------------------------------------
    // Current animation state.
    //
    // true  -> Opening / Open
    // false -> Closing / Closed
    //----------------------------------------------------------
    bool opened;
};