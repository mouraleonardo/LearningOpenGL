/*
    ============================================================
    Mesh.cpp

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    Implements the Mesh class which stores geometry data
    on the GPU and provides functionality to render that
    geometry.

    A Mesh represents a collection of vertices that form
    an object such as:

        • Car Body
        • Wheels
        • Wheel Rims
        • Smoke Particles

    Responsibilities:
        • Create OpenGL buffers
        • Upload vertex data to the GPU
        • Configure vertex attributes
        • Draw geometry
        • Release GPU resources

    OpenGL Objects Used:

        VAO (Vertex Array Object)
            Stores vertex attribute configuration.

        VBO (Vertex Buffer Object)
            Stores actual vertex data.

    Vertex Layout:

        Each vertex contains:

            x, y, z,
            r, g, b

        Position:
            3 floats

        Color:
            3 floats

        Total:
            6 floats per vertex

    Example Vertex:

        1.0f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f

        Position:
            (1.0, 0.5, 0.0)

        Color:
            Red

    Rendering Process:

        CPU Vertex Data
              ↓
            VBO
              ↓
            VAO
              ↓
        Vertex Shader
              ↓
        Fragment Shader
              ↓
            Screen

    ============================================================
*/
#include "Mesh.h"

// OpenGL functions
#include <glew.h>

/*
    Constructor

    Receives a list of vertices and uploads
    them to GPU memory.

    Each vertex contains:

        Position (x,y,z)
        Color (r,g,b)

    Total:
        6 floats per vertex
*/
Mesh::Mesh(
    const std::vector<float>& vertices)
{
    /*
        Calculate total number of vertices.

        Since each vertex contains 6 floats:

            x y z r g b

        Total Vertices =
            total float count ÷ 6
    */
    vertexCount =
        static_cast<unsigned int>(
            vertices.size() / 6);

    /*
        =================================================
        CREATE OPENGL OBJECTS
        =================================================
    */

    /*
        Generate a Vertex Array Object.

        VAO stores information about:

            • Vertex attributes
            • Buffer bindings
            • Data layout
    */
    glGenVertexArrays(
        1,
        &VAO);

    /*
        Generate a Vertex Buffer Object.

        VBO stores actual vertex data.
    */
    glGenBuffers(
        1,
        &VBO);

    /*
        =================================================
        BIND VAO
        =================================================

        Any attribute configuration that follows
        will be stored inside this VAO.
    */
    glBindVertexArray(
        VAO);

    /*
        =================================================
        BIND VBO
        =================================================

        Makes this VBO the active buffer.
    */
    glBindBuffer(
        GL_ARRAY_BUFFER,
        VBO);

    /*
        =================================================
        UPLOAD VERTEX DATA TO GPU
        =================================================

        Parameters:

            Target Buffer
            Size in Bytes
            Data Pointer
            Usage Pattern

        GL_STATIC_DRAW:
            Data rarely changes after upload.
    */
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW);

    /*
        =================================================
        ATTRIBUTE 0
        POSITION DATA
        =================================================

        Vertex Layout:

            x y z r g b
            ↑ ↑ ↑
            Position

        Location:
            layout(location = 0)

        Matches:

            in vec3 aPos;

        inside the vertex shader.
    */
    glVertexAttribPointer(
        0,                  // Attribute location
        3,                  // Number of values
        GL_FLOAT,           // Data type
        GL_FALSE,           // No normalization
        6 * sizeof(float),  // Size of entire vertex
        (void*)0);          // Position starts at beginning

    /*
        Enable attribute location 0.
    */
    glEnableVertexAttribArray(0);

    /*
        =================================================
        ATTRIBUTE 1
        COLOR DATA
        =================================================

        Vertex Layout:

            x y z r g b
                  ↑ ↑ ↑
                   Color

        Location:
            layout(location = 1)

        Matches:

            in vec3 aColor;

        inside the vertex shader.
    */
    glVertexAttribPointer(
        1,                          // Attribute location
        3,                          // RGB values
        GL_FLOAT,                   // Data type
        GL_FALSE,                   // No normalization
        6 * sizeof(float),          // Size of entire vertex
        (void*)(3 * sizeof(float))); // Skip x,y,z

    /*
        Enable attribute location 1.
    */
    glEnableVertexAttribArray(1);

    /*
        Unbind VAO.

        Prevents accidental modification later.
    */
    glBindVertexArray(0);
}

/*
    Draw()

    Renders the mesh using triangles.

    Called by the Renderer class whenever
    the object needs to appear on screen.
*/
void Mesh::Draw() const
{
    /*
        Activate this mesh's VAO.

        Restores all vertex attribute settings.
    */
    glBindVertexArray(VAO);

    /*
        Draw all vertices as triangles.

        Parameters:

            GL_TRIANGLES
                Every 3 vertices form a triangle

            Start Index
                0

            Vertex Count
                Total vertices in mesh
    */
    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount);

    /*
        Unbind VAO after rendering.
    */
    glBindVertexArray(0);
}

/*
    Destructor

    Automatically called when the Mesh
    object is destroyed.

    Releases GPU resources and prevents
    memory leaks.
*/
Mesh::~Mesh()
{
    /*
        Delete Vertex Array Object.
    */
    glDeleteVertexArrays(
        1,
        &VAO);

    /*
        Delete Vertex Buffer Object.
    */
    glDeleteBuffers(
        1,
        &VBO);
}

/*
    ============================================================
    SUMMARY

    Constructor:
        • Creates VAO
        • Creates VBO
        • Uploads vertex data
        • Configures attributes

    Draw():
        • Binds VAO
        • Renders triangles

    Destructor:
        • Frees GPU memory

    OpenGL Objects:

        VAO
            Stores vertex configuration

        VBO
            Stores vertex data

    Vertex Structure:

        x, y, z, r, g, b

        Position → Attribute 0
        Color    → Attribute 1

    This class serves as the bridge between
    CPU vertex data and GPU rendering.
    ============================================================
*/