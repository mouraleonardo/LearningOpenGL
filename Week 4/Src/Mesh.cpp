#include "Mesh.h"
#include <glew.h>

/*
    Vertex Data

    Each vertex contains:

    - Position (X, Y, Z)
    - Color (R, G, B)

    The cube is defined using 8 vertices.
    Each vertex has a unique color that will
    be interpolated across the cube faces by
    the fragment shader.
*/
float vertices[] =
{
    // Position XYZ             // RGB

    // Front Face Vertices
    -0.5f,-0.5f, 0.5f,         1.0f,0.0f,0.0f,   // Red
     0.5f,-0.5f, 0.5f,         0.0f,1.0f,0.0f,   // Green
     0.5f, 0.5f, 0.5f,         0.0f,0.0f,1.0f,   // Blue
    -0.5f, 0.5f, 0.5f,         1.0f,1.0f,0.0f,   // Yellow

    // Back Face Vertices
    -0.5f,-0.5f,-0.5f,         1.0f,0.0f,1.0f,   // Magenta
     0.5f,-0.5f,-0.5f,         0.0f,1.0f,1.0f,   // Cyan
     0.5f, 0.5f,-0.5f,         1.0f,1.0f,1.0f,   // White
    -0.5f, 0.5f,-0.5f,         0.2f,0.2f,0.2f    // Gray
};

/*
    Index Data (EBO)

    The Element Buffer Object stores indices
    that define how vertices are connected to
    form triangles.

    Each face of the cube is composed of
    two triangles.

    Total:
    - 6 faces
    - 12 triangles
    - 36 indices

    Using an EBO avoids duplicating vertex data,
    making rendering more efficient.
*/
unsigned int indices[] =
{
    // Front Face
    0,1,2,
    2,3,0,

    // Right Face
    1,5,6,
    6,2,1,

    // Back Face
    5,4,7,
    7,6,5,

    // Left Face
    4,0,3,
    3,7,4,

    // Top Face
    3,2,6,
    6,7,3,

    // Bottom Face
    4,5,1,
    1,0,4
};

/*
    Constructor

    Creates and initializes:

    - VAO (Vertex Array Object)
    - VBO (Vertex Buffer Object)
    - EBO (Element Buffer Object)

    Uploads vertex and index data to the GPU
    and configures vertex attributes.
*/
Mesh::Mesh()
{
    // Generate OpenGL objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO to store vertex configuration
    glBindVertexArray(VAO);

    /*
        Upload vertex data to GPU memory
        through the Vertex Buffer Object.
    */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    /*
        Upload index data to GPU memory
        through the Element Buffer Object.
    */
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW);

    /*
        Vertex Attribute 0

        Position Data

        Layout:
        X, Y, Z
    */
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0);

    glEnableVertexAttribArray(0);

    /*
        Vertex Attribute 1

        Color Data

        Layout:
        R, G, B

        Starts after the first three floats
        containing the position data.
    */
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

/*
    Draw Function

    Binds the VAO and renders the cube using
    indexed drawing.

    glDrawElements uses the EBO indices to
    determine which vertices form each triangle.
*/
void Mesh::Draw()
{
    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        36,
        GL_UNSIGNED_INT,
        0);
}

/*
    Destructor

    Releases GPU resources allocated for:

    - VAO
    - VBO
    - EBO

    Prevents memory leaks and ensures proper
    cleanup when the Mesh object is destroyed.
*/
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}