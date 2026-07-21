/*
    ============================================================
    Mesh - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This class represents a simple 3D mesh stored entirely in
    GPU memory.

    In this project, the mesh consists of a textured cube built
    procedurally in code. The geometry is uploaded to the GPU
    using Vertex Buffer Objects (VBO) and managed through a
    Vertex Array Object (VAO).

    The mesh stores all information required for rendering,
    including vertex positions, surface normals, and texture
    coordinates.

    Responsibilities:

        • Generate cube geometry
        • Store vertex data
        • Upload geometry to GPU memory
        • Configure vertex attributes
        • Render the mesh
        • Manage GPU resources

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLEW
        • GLM
        • C++

    Learning Topics:

        • Mesh Representation
        • Vertex Buffers (VBO)
        • Vertex Arrays (VAO)
        • Vertex Attributes
        • Texture Coordinates (UV)
        • Surface Normals
        • GPU Memory Management
        • Procedural Geometry

    ============================================================
*/

#pragma once

#include <vector>

#include <glew.h>

#include <glm.hpp>

//
//--------------------------------------------------------------
// Vertex
//--------------------------------------------------------------
//
// Represents a single vertex of the mesh.
//
// Each vertex stores:
//
//      • Position
//      • Normal
//      • Texture Coordinates
//
// These attributes are sent to the Vertex Shader where they
// become the input attributes of the rendering pipeline.
//
struct Vertex
{
    //----------------------------------------------------------
    // Position in Local Space.
    //----------------------------------------------------------
    glm::vec3 Position;

    //----------------------------------------------------------
    // Surface normal.
    //
    // Used for lighting calculations.
    //----------------------------------------------------------
    glm::vec3 Normal;

    //----------------------------------------------------------
    // Texture Coordinates (UV).
    //
    // Defines which region of the texture corresponds
    // to this vertex.
    //----------------------------------------------------------
    glm::vec2 TexCoord;
};

//
//--------------------------------------------------------------
// Mesh
//--------------------------------------------------------------
//
// Represents a renderable mesh.
//
// In this project, the mesh is a cube generated
// procedurally in code.
//
class Mesh
{
public:

    //----------------------------------------------------------
    // Constructor.
    //
    // Creates the cube geometry and uploads it to the GPU.
    //----------------------------------------------------------
    Mesh();

    //----------------------------------------------------------
    // Destructor.
    //
    // Releases all GPU resources associated with the mesh.
    //----------------------------------------------------------
    ~Mesh();

    //----------------------------------------------------------
    // Renders the mesh.
    //
    // The mesh is rendered using glDrawArrays().
    //----------------------------------------------------------
    void Draw() const;

private:

    //----------------------------------------------------------
    // Vertex Array Object.
    //
    // Stores the complete vertex attribute configuration.
    //----------------------------------------------------------
    GLuint VAO;

    //----------------------------------------------------------
    // Vertex Buffer Object.
    //
    // Stores the vertex data inside GPU memory.
    //----------------------------------------------------------
    GLuint VBO;

    //----------------------------------------------------------
    // CPU-side vertex storage.
    //
    // The geometry is generated here before being uploaded
    // to the GPU.
    //----------------------------------------------------------
    std::vector<Vertex> vertices;

    //----------------------------------------------------------
    // Generates the cube geometry.
    //
    // Creates all vertices, normals, and texture coordinates.
    //----------------------------------------------------------
    void BuildCube();

    //----------------------------------------------------------
    // Uploads the mesh to GPU memory.
    //
    // Creates the VAO and VBO and configures all vertex
    // attributes.
    //----------------------------------------------------------
    void SetupMesh();
};