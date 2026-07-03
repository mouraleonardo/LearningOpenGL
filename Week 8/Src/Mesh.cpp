#include "Mesh.h"

#include <glew.h>

Mesh::Mesh(
    const std::vector<float>& vertices)
{
    //--------------------------------------------------
    // Vertex Count
    //--------------------------------------------------

    vertexCount =
        static_cast<unsigned int>(
            vertices.size() / 6);

    //--------------------------------------------------
    // Create OpenGL Objects
    //--------------------------------------------------

    glGenVertexArrays(
        1,
        &VAO);

    glGenBuffers(
        1,
        &VBO);

    //--------------------------------------------------
    // Bind VAO
    //--------------------------------------------------

    glBindVertexArray(
        VAO);

    //--------------------------------------------------
    // Upload Vertex Data
    //--------------------------------------------------

    glBindBuffer(
        GL_ARRAY_BUFFER,
        VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size()
        * sizeof(float),

        vertices.data(),

        GL_STATIC_DRAW);

    //--------------------------------------------------
    // Position Attribute
    //--------------------------------------------------

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0);

    glEnableVertexAttribArray(
        0);

    //--------------------------------------------------
    // Color Attribute
    //--------------------------------------------------

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(
        1);

    //--------------------------------------------------
    // Cleanup
    //--------------------------------------------------

    glBindVertexArray(
        0);
}

void Mesh::Draw() const
{
    glBindVertexArray(
        VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount);

    glBindVertexArray(
        0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(
        1,
        &VAO);

    glDeleteBuffers(
        1,
        &VBO);
}