#include "Mesh.h"

Mesh::Mesh()
{
    BuildCube();
    SetupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::BuildCube()
{
    vertices =
    {
        //=========================
        // Frente (+Z)
        //=========================

        {{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
        {{ 0.5f,-0.5f, 0.5f},{0,0,1},{1,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},

        {{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},
        {{-0.5f, 0.5f, 0.5f},{0,0,1},{0,1}},

        //=========================
        // Trás (-Z)
        //=========================

        {{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},
        {{-0.5f,-0.5f,-0.5f},{0,0,-1},{1,0}},
        {{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},

        {{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},
        {{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},
        {{ 0.5f, 0.5f,-0.5f},{0,0,-1},{0,1}},

        //=========================
        // Esquerda (-X)
        //=========================

        {{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
        {{-0.5f,-0.5f, 0.5f},{-1,0,0},{1,0}},
        {{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},

        {{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
        {{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},
        {{-0.5f, 0.5f,-0.5f},{-1,0,0},{0,1}},

        //=========================
        // Direita (+X)
        //=========================

        {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},
        {{ 0.5f,-0.5f,-0.5f},{1,0,0},{1,0}},
        {{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},

        {{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},
        {{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},
        {{ 0.5f, 0.5f, 0.5f},{1,0,0},{0,1}},

        //=========================
        // Topo (+Y)
        //=========================

        {{-0.5f, 0.5f, 0.5f},{0,1,0},{0,0}},
        {{ 0.5f, 0.5f, 0.5f},{0,1,0},{1,0}},
        {{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,1}},

        {{-0.5f, 0.5f, 0.5f},{0,1,0},{0,0}},
        {{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,1}},
        {{-0.5f, 0.5f,-0.5f},{0,1,0},{0,1}},

        //=========================
        // Base (-Y)
        //=========================

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
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Normal)
    );
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, TexCoord)
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}