#ifndef RENDERER_H
#define RENDERER_H

#include <glew.h>

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"

#include "Camera.h"
#include "World.h"
#include "Tree.h"
#include "Door.h"

class Renderer
{
private:

    //--------------------------------------------------
    // Shader
    //--------------------------------------------------

    Shader* shader;

    //--------------------------------------------------
    // Uniforms
    //--------------------------------------------------

    int mvpLocation;

    //--------------------------------------------------
    // Matrices
    //--------------------------------------------------

    glm::mat4 projection;

    //--------------------------------------------------
    // World Meshes
    //--------------------------------------------------

    Mesh* groundMesh;

    Mesh* trunkMesh;

    Mesh* leavesMesh;

    Mesh* doorMesh;

private:

    //--------------------------------------------------
    // Internal Draw
    //--------------------------------------------------

    void DrawMesh(
        Mesh* mesh,
        const glm::mat4& model,
        const glm::mat4& view);

    void DrawGround(
        const glm::mat4& view);

    void DrawTree(
        const Tree& tree,
        const glm::mat4& view);

    void DrawDoor(
        const Door& door,
        const glm::mat4& view);

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    Renderer();

    //--------------------------------------------------
    // Initialization
    //--------------------------------------------------

    bool Initialize(
        int screenWidth,
        int screenHeight);

    //--------------------------------------------------
    // Shader
    //--------------------------------------------------

    void SetShader(
        Shader* shaderProgram);

    //--------------------------------------------------
    // Frame
    //--------------------------------------------------

    void BeginFrame();

    void EndFrame();

    //--------------------------------------------------
    // Render Pass
    //--------------------------------------------------

    void RenderWorld(
        const World& world,
        const Camera& camera);

    //--------------------------------------------------
    // Cleanup
    //--------------------------------------------------

    void Shutdown();

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Renderer();
};

#endif