/*
    ============================================================
    Treasure Chest - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This class represents an interactive hollow Treasure Chest.
    A shared cube mesh is instanced as thin floor/roof and wall
    pieces, creating visible cavities in both base and lid.

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
    // Base and lid are assembled from ten transformed instances
    // of the shared cube: five shell pieces for each half.
    //----------------------------------------------------------
    void Draw(Shader& shader);

private:
    //----------------------------------------------------------
    // Draws one shell piece relative to a parent transform.
    // Keeping the parent matrix allows every lid wall to inherit
    // exactly the same hinge rotation (hierarchical transform).
    //----------------------------------------------------------
    void DrawBox(
        Shader& shader,
        const glm::mat4& parent,
        const glm::vec3& center,
        const glm::vec3& size
    );


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

    // Thickness of the wooden shell used by the base and lid.
    float wallThickness;

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
