#include "Renderer.h"

#include <vector>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

namespace
{
    //--------------------------------------------------
    // Vertex Helpers
    //--------------------------------------------------

    void AddTriangle(
        std::vector<float>& vertices,

        float x1, float y1, float z1,
        float x2, float y2, float z2,
        float x3, float y3, float z3,

        float r,
        float g,
        float b)
    {
        vertices.insert(
            vertices.end(),
            {
                x1,y1,z1,r,g,b,
                x2,y2,z2,r,g,b,
                x3,y3,z3,r,g,b
            });
    }

    //--------------------------------------------------
    // Plane
    //--------------------------------------------------

    std::vector<float> CreatePlane(
        float size,
        float r,
        float g,
        float b)
    {
        std::vector<float> vertices;

        float h =
            size * 0.5f;

        AddTriangle(
            vertices,

            -h, 0.0f, -h,
            h, 0.0f, -h,
            h, 0.0f, h,

            r, g, b);

        AddTriangle(
            vertices,

            -h, 0.0f, -h,
            h, 0.0f, h,
            -h, 0.0f, h,

            r, g, b);

        return vertices;
    }

    //--------------------------------------------------
    // Cube
    //--------------------------------------------------

    std::vector<float> CreateCube(
        float size,
        float r,
        float g,
        float b)
    {
        float h =
            size * 0.5f;

        std::vector<float> v;

        //--------------------------------------------------
        // Front
        //--------------------------------------------------

        AddTriangle(v,
            -h, -h, h,
            h, -h, h,
            h, h, h,
            r, g, b);

        AddTriangle(v,
            -h, -h, h,
            h, h, h,
            -h, h, h,
            r, g, b);

        //--------------------------------------------------
        // Back
        //--------------------------------------------------

        AddTriangle(v,
            h, -h, -h,
            -h, -h, -h,
            -h, h, -h,
            r, g, b);

        AddTriangle(v,
            h, -h, -h,
            -h, h, -h,
            h, h, -h,
            r, g, b);

        //--------------------------------------------------
        // Left
        //--------------------------------------------------

        AddTriangle(v,
            -h, -h, -h,
            -h, -h, h,
            -h, h, h,
            r, g, b);

        AddTriangle(v,
            -h, -h, -h,
            -h, h, h,
            -h, h, -h,
            r, g, b);

        //--------------------------------------------------
        // Right
        //--------------------------------------------------

        AddTriangle(v,
            h, -h, h,
            h, -h, -h,
            h, h, -h,
            r, g, b);

        AddTriangle(v,
            h, -h, h,
            h, h, -h,
            h, h, h,
            r, g, b);

        //--------------------------------------------------
        // Top
        //--------------------------------------------------

        AddTriangle(v,
            -h, h, h,
            h, h, h,
            h, h, -h,
            r, g, b);

        AddTriangle(v,
            -h, h, h,
            h, h, -h,
            -h, h, -h,
            r, g, b);

        //--------------------------------------------------
        // Bottom
        //--------------------------------------------------

        AddTriangle(v,
            -h, -h, -h,
            h, -h, -h,
            h, -h, h,
            r, g, b);

        AddTriangle(v,
            -h, -h, -h,
            h, -h, h,
            -h, -h, h,
            r, g, b);

        return v;
    }
}

//--------------------------------------------------
// Constructor
//--------------------------------------------------

Renderer::Renderer()
{
    shader = nullptr;

    mvpLocation = -1;

    groundMesh = nullptr;
    trunkMesh = nullptr;
    leavesMesh = nullptr;
    doorMesh = nullptr;
}

//--------------------------------------------------
// Initialization
//--------------------------------------------------

bool Renderer::Initialize(
    int screenWidth,
    int screenHeight)
{
    projection =
        glm::perspective(
            glm::radians(
                60.0f),

            static_cast<float>(
                screenWidth)
            /
            static_cast<float>(
                screenHeight),

            0.1f,
            100.0f);

    //--------------------------------------------------
    // Ground
    //--------------------------------------------------

    groundMesh =
        new Mesh(
            CreatePlane(
                50.0f,
                0.2f,
                0.7f,
                0.2f));

    //--------------------------------------------------
    // Tree Trunk
    //--------------------------------------------------

    trunkMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.55f,
                0.27f,
                0.07f));

    //--------------------------------------------------
    // Tree Leaves
    //--------------------------------------------------

    leavesMesh =
        new Mesh(
            CreateCube(
                2.0f,
                0.0f,
                0.6f,
                0.0f));

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    doorMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.5f,
                0.3f,
                0.1f));

    return true;
}

//--------------------------------------------------
// Shader
//--------------------------------------------------

void Renderer::SetShader(
    Shader* shaderProgram)
{
    shader =
        shaderProgram;

    if (shader)
    {
        mvpLocation =
            static_cast<int>(
                glGetUniformLocation(
                    shader->GetID(),
                    "mvp"));
    }
}

//--------------------------------------------------
// Frame
//--------------------------------------------------

void Renderer::BeginFrame()
{
    glEnable(
        GL_DEPTH_TEST);

    glClearColor(
        0.53f,
        0.81f,
        0.92f,
        1.0f);

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT);

    if (shader)
    {
        shader->Use();
    }
}

void Renderer::EndFrame()
{
}

//--------------------------------------------------
// Internal Draw
//--------------------------------------------------

void Renderer::DrawMesh(
    Mesh* mesh,
    const glm::mat4& model,
    const glm::mat4& view)
{
    if (!mesh)
    {
        return;
    }

    glm::mat4 mvp =
        projection *
        view *
        model;

    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(
            mvp));

    mesh->Draw();
}

void Renderer::DrawGround(
    const glm::mat4& view)
{
    glm::mat4 model =
        glm::mat4(1.0f);

    DrawMesh(
        groundMesh,
        model,
        view);
}

void Renderer::DrawTree(
    const Tree& tree,
    const glm::mat4& view)
{
    glm::vec3 position =
        tree.GetPosition();

    //--------------------------------------------------
    // Trunk
    //--------------------------------------------------

    glm::mat4 trunkModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                position.x,
                1.0f,
                position.z));

    trunkModel =
        glm::scale(
            trunkModel,
            glm::vec3(
                tree.GetTrunkWidth(),
                tree.GetTrunkHeight(),
                tree.GetTrunkWidth()));

    DrawMesh(
        trunkMesh,
        trunkModel,
        view);

    //--------------------------------------------------
    // Leaves
    //--------------------------------------------------

    glm::mat4 leavesModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                position.x,
                3.0f,
                position.z));

    leavesModel =
        glm::scale(
            leavesModel,
            glm::vec3(
                tree.GetLeavesSize()));

    DrawMesh(
        leavesMesh,
        leavesModel,
        view);
}

void Renderer::DrawDoor(
    const Door& door,
    const glm::mat4& view)
{
    if (door.IsOpen())
    {
        return;
    }

    glm::vec3 position =
        door.GetPosition();

    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            position);

    model =
        glm::scale(
            model,
            glm::vec3(
                door.GetWidth(),
                door.GetHeight(),
                door.GetDepth()));

    DrawMesh(
        doorMesh,
        model,
        view);
}

//--------------------------------------------------
// Render Pass
//--------------------------------------------------

void Renderer::RenderWorld(
    const World& world,
    const Camera& camera)
{
    glm::mat4 view =
        camera.GetViewMatrix();

    DrawGround(
        view);

    for (const Tree& tree :
        world.GetTrees())
    {
        DrawTree(
            tree,
            view);
    }

    DrawDoor(
        world.GetDoor(),
        view);
}

//--------------------------------------------------
// Cleanup
//--------------------------------------------------

void Renderer::Shutdown()
{
    delete groundMesh;
    groundMesh = nullptr;

    delete trunkMesh;
    trunkMesh = nullptr;

    delete leavesMesh;
    leavesMesh = nullptr;

    delete doorMesh;
    doorMesh = nullptr;
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Renderer::~Renderer()
{
    Shutdown();
}