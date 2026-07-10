/*
    ============================================================
    Mesh - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This file implements a simple Mesh class responsible for
    creating and rendering a textured cube.

    The cube is entirely generated in code using vertex data.
    Each face contains its own vertices, normals and texture
    coordinates, allowing every face to have independent
    lighting and texture mapping.

    The mesh is uploaded to GPU memory using Vertex Buffer
    Objects (VBO) and Vertex Array Objects (VAO).

    Responsibilities:

        • Build cube geometry
        • Upload vertex data to the GPU
        • Configure vertex attributes
        • Render the cube
        • Release GPU resources

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLEW
        • GLM
        • C++

    Learning Topics:

        • Mesh Generation
        • Vertex Buffers (VBO)
        • Vertex Arrays (VAO)
        • Vertex Attributes
        • Texture Coordinates
        • Vertex Normals
        • GPU Memory
        • Draw Calls

    ============================================================
*/

#include "Mesh.h"

Mesh::Mesh()
{
    //----------------------------------------------------------
    // Build the cube geometry.
    //----------------------------------------------------------

    BuildCube();

    //----------------------------------------------------------
    // Upload the mesh to the GPU.
    //----------------------------------------------------------

    SetupMesh();
}

Mesh::~Mesh()
{
    //----------------------------------------------------------
    // Release GPU resources.
    //----------------------------------------------------------

    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);
}

void Mesh::BuildCube()
{
    //----------------------------------------------------------
    // Create the cube geometry.
    //
    // Every face owns its own vertices because each face has
    // a different normal vector and texture coordinates.
    //
    // Cube:
    //
    //          +Y
    //           ↑
    //
    //      (-X)   (+X)
    //
    //           •
    //          /
    //       +Z
    //
    //----------------------------------------------------------

    vertices =
    {
        //------------------------------------------------------
        // Front Face (+Z)
        //------------------------------------------------------

        {{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
        {{ 0.5f,-0.5f, 0.5f},{0,0,1},{1,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},

        {{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},
        {{-0.5f, 0.5f, 0.5f},{0,0,1},{0,1}},

        //------------------------------------------------------
        // Back Face (-Z)
        //------------------------------------------------------

        {{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},
        {{-0.5f,-0.5f,-0.5f},{0,0,-1},{1,0}},
        {{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},

        {{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},
        {{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},
        {{ 0.5f, 0.5f,-0.5f},{0,0,-1},{0,1}},

        //------------------------------------------------------
        // Left Face (-X)
        //------------------------------------------------------

        {{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
        {{-0.5f,-0.5f, 0.5f},{-1,0,0},{1,0}},
        {{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},

        {{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
        {{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},
        {{-0.5f, 0.5f,-0.5f},{-1,0,0},{0,1}},

        //------------------------------------------------------
        // Right Face (+X)
        //------------------------------------------------------

        {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},
        {{ 0.5f,-0.5f,-0.5f},{1,0,0},{1,0}},
        {{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},

        {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},
        {{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},
        {{ 0.5f, 0.5f, 0.5f},{1,0,0},{0,1}},

        //------------------------------------------------------
        // Top Face (+Y)
        //------------------------------------------------------

        {{-0.5f, 0.5f, 0.5f},{0,1,0},{0,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,1,0},{1,0}},
        {{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,1}},

        {{-0.5f, 0.5f, 0.5f},{0,1,0},{0,0}},
        {{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,1}},
        {{-0.5f, 0.5f,-0.5f},{0,1,0},{0,1}},

        //------------------------------------------------------
        // Bottom Face (-Y)
        //------------------------------------------------------

        {{-0.5f,-0.5f,-0.5f},{0,-1,0},{0,0}},
        {{ 0.5f,-0.5f,-0.5f},{0,-1,0},{1,0}},
        {{ 0.5f,-0.5f, 0.5f},{0,-1,0},{1,1}},

        {{-0.5f,-0.5f,-0.5f},{0,-1,0},{0,0}},
        {{ 0.5f,-0.5f, 0.5f},{0,-1,0},{1,1}},
        {{-0.5f,-0.5f, 0.5f},{0,-1,0},{0,1}},
    };
}

void Mesh::SetupMesh()
{
    //----------------------------------------------------------
    // Create the GPU objects.
    //----------------------------------------------------------

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    //----------------------------------------------------------
    // Bind the Vertex Array Object.
    //----------------------------------------------------------

    glBindVertexArray(VAO);

    //----------------------------------------------------------
    // Upload vertex data to GPU memory.
    //----------------------------------------------------------

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    //----------------------------------------------------------
    // Vertex Attribute 0
    //
    // Position (vec3)
    //----------------------------------------------------------

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    //----------------------------------------------------------
    // Vertex Attribute 1
    //
    // Normal (vec3)
    //----------------------------------------------------------

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Normal)
    );

    glEnableVertexAttribArray(1);

    //----------------------------------------------------------
    // Vertex Attribute 2
    //
    // Texture Coordinates (vec2)
    //----------------------------------------------------------

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, TexCoord)
    );

    glEnableVertexAttribArray(2);

    //----------------------------------------------------------
    // Unbind the VAO.
    //----------------------------------------------------------

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    //----------------------------------------------------------
    // Bind the VAO before rendering.
    //----------------------------------------------------------

    glBindVertexArray(VAO);

    //----------------------------------------------------------
    // Render the cube.
    //
    // The cube contains:
    //
    //      6 Faces
    //      2 Triangles per Face
    //      3 Vertices per Triangle
    //
    // Total:
    //
    //      36 Vertices
    //----------------------------------------------------------

    glDrawArrays(
        GL_TRIANGLES,
        0,
        36
    );

    //----------------------------------------------------------
    // Unbind the VAO.
    //----------------------------------------------------------

    glBindVertexArray(0);
}