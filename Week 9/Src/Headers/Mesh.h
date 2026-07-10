#pragma once

#include <vector>
#include <glew.h>
#include <glm.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

class Mesh
{
public:

    Mesh();

    ~Mesh();

    void Draw() const;

private:

    GLuint VAO;
    GLuint VBO;

    std::vector<Vertex> vertices;

    void BuildCube();

    void SetupMesh();
};