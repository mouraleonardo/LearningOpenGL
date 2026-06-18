#include "Renderer.h"

#include <vector>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

namespace
{
    //--------------------------------------------------
    // Vertex Helper
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

        AddTriangle(
            v,

            -h, -h, h,
            h, -h, h,
            h, h, h,

            r, g, b);

        AddTriangle(
            v,

            -h, -h, h,
            h, h, h,
            -h, h, h,

            r, g, b);

        //--------------------------------------------------
        // Back
        //--------------------------------------------------

        AddTriangle(
            v,

            h, -h, -h,
            -h, -h, -h,
            -h, h, -h,

            r, g, b);

        AddTriangle(
            v,

            h, -h, -h,
            -h, h, -h,
            h, h, -h,

            r, g, b);

        //--------------------------------------------------
        // Left
        //--------------------------------------------------

        AddTriangle(
            v,

            -h, -h, -h,
            -h, -h, h,
            -h, h, h,

            r, g, b);

        AddTriangle(
            v,

            -h, -h, -h,
            -h, h, h,
            -h, h, -h,

            r, g, b);

        //--------------------------------------------------
        // Right
        //--------------------------------------------------

        AddTriangle(
            v,

            h, -h, h,
            h, -h, -h,
            h, h, -h,

            r, g, b);

        AddTriangle(
            v,

            h, -h, h,
            h, h, -h,
            h, h, h,

            r, g, b);

        //--------------------------------------------------
        // Top
        //--------------------------------------------------

        AddTriangle(
            v,

            -h, h, h,
            h, h, h,
            h, h, -h,

            r, g, b);

        AddTriangle(
            v,

            -h, h, h,
            h, h, -h,
            -h, h, -h,

            r, g, b);

        //--------------------------------------------------
        // Bottom
        //--------------------------------------------------

        AddTriangle(
            v,

            -h, -h, -h,
            h, -h, -h,
            h, -h, h,

            r, g, b);

        AddTriangle(
            v,

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

    projection =
        glm::mat4(1.0f);

    groundMesh = nullptr;

    trunkMesh = nullptr;
    leavesMesh = nullptr;

    doorMesh = nullptr;

    castleWallMesh = nullptr;
    castleTowerMesh = nullptr;
    castleRoofMesh = nullptr;
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
            1000.0f);

    //--------------------------------------------------
    // Ground
    //--------------------------------------------------

    groundMesh =
        new Mesh(
            CreatePlane(
                500.0f,
                0.25f,
                0.70f,
                0.25f));

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
                1.0f,
                0.0f,
                0.60f,
                0.0f));

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    doorMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.45f,
                0.25f,
                0.10f));

    //--------------------------------------------------
    // Castle Wall
    //--------------------------------------------------

    castleWallMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.70f,
                0.70f,
                0.75f));

    //--------------------------------------------------
    // Castle Tower
    //--------------------------------------------------

    castleTowerMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.60f,
                0.60f,
                0.65f));

    //--------------------------------------------------
    // Castle Roof
    //--------------------------------------------------

    castleRoofMesh =
        new Mesh(
            CreateCube(
                1.0f,
                0.45f,
                0.15f,
                0.15f));

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

//--------------------------------------------------
// Ground
//--------------------------------------------------

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

//--------------------------------------------------
// Tree
//--------------------------------------------------

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
                tree.GetTrunkHeight() * 0.5f,
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
                tree.GetTrunkHeight()
                +
                tree.GetLeavesSize() * 0.5f,
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

//--------------------------------------------------
// Door
//--------------------------------------------------

void Renderer::DrawDoor(
    const Door& door,
    const glm::mat4& view)
{
    glm::vec3 position =
        door.GetPosition();

    //--------------------------------------------------
    // Base Transform
    //--------------------------------------------------

    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                position.x,
                position.y +
                door.GetHeight() * 0.5f,
                position.z));

    //--------------------------------------------------
    // Move To Hinge
    //--------------------------------------------------

    model =
        glm::translate(
            model,
            glm::vec3(
                -door.GetWidth() * 0.5f,
                0.0f,
                0.0f));

    //--------------------------------------------------
    // Rotate Around Hinge
    //--------------------------------------------------

    model =
        glm::rotate(
            model,
            glm::radians(
                door.GetCurrentAngle()),
            glm::vec3(
                0.0f,
                1.0f,
                0.0f));

    //--------------------------------------------------
    // Return To Center
    //--------------------------------------------------

    model =
        glm::translate(
            model,
            glm::vec3(
                door.GetWidth() * 0.5f,
                0.0f,
                0.0f));

    //--------------------------------------------------
    // Scale
    //--------------------------------------------------

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
// Castle
//--------------------------------------------------

void Renderer::DrawCastle(
    const World& world,
    const glm::mat4& view)
{
    glm::vec3 castlePosition =
        world.GetCastlePosition();

    //--------------------------------------------------
// Front Left Wall
//--------------------------------------------------

    glm::mat4 frontLeftWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x - 5.0f,
                castlePosition.y + 5.0f,
                castlePosition.z - 6.0f));

    frontLeftWall =
        glm::scale(
            frontLeftWall,
            glm::vec3(
                6.0f,
                10.0f,
                1.0f));

    DrawMesh(
        castleWallMesh,
        frontLeftWall,
        view);

    //--------------------------------------------------
    // Front Right Wall
    //--------------------------------------------------

    glm::mat4 frontRightWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x + 5.0f,
                castlePosition.y + 5.0f,
                castlePosition.z - 6.0f));

    frontRightWall =
        glm::scale(
            frontRightWall,
            glm::vec3(
                6.0f,
                10.0f,
                1.0f));

    //--------------------------------------------------
    // Wall Above Door
    //--------------------------------------------------

    DrawMesh(
        castleWallMesh,
        frontRightWall,
        view);

    glm::mat4 frontTopWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x,
                castlePosition.y + 8.5f,
                castlePosition.z - 6.0f));

    frontTopWall =
        glm::scale(
            frontTopWall,
            glm::vec3(
                4.0f,
                5.0f,
                1.0f));

    DrawMesh(
        castleWallMesh,
        frontTopWall,
        view);

    //--------------------------------------------------
    // Back Wall
    //--------------------------------------------------

    glm::mat4 backWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x,
                castlePosition.y + 5.0f,
                castlePosition.z + 6.0f));

    backWall =
        glm::scale(
            backWall,
            glm::vec3(
                16.0f,
                10.0f,
                1.0f));

    DrawMesh(
        castleWallMesh,
        backWall,
        view);

    //--------------------------------------------------
    // Left Wall
    //--------------------------------------------------

    glm::mat4 leftWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x - 8.0f,
                castlePosition.y + 5.0f,
                castlePosition.z));

    leftWall =
        glm::scale(
            leftWall,
            glm::vec3(
                1.0f,
                10.0f,
                12.0f));

    DrawMesh(
        castleWallMesh,
        leftWall,
        view);

    //--------------------------------------------------
    // Right Wall
    //--------------------------------------------------

    glm::mat4 rightWall =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x + 8.0f,
                castlePosition.y + 5.0f,
                castlePosition.z));

    rightWall =
        glm::scale(
            rightWall,
            glm::vec3(
                1.0f,
                10.0f,
                12.0f));

    DrawMesh(
        castleWallMesh,
        rightWall,
        view);

    //--------------------------------------------------
    // Towers
    //--------------------------------------------------

    const glm::vec3 towerOffsets[4] =
    {
        {-8.0f, 7.0f, -6.0f},
        { 8.0f, 7.0f, -6.0f},
        {-8.0f, 7.0f,  6.0f},
        { 8.0f, 7.0f,  6.0f}
    };

    for (int i = 0;
        i < 4;
        i++)
    {
        glm::mat4 towerModel =
            glm::translate(
                glm::mat4(1.0f),
                castlePosition +
                towerOffsets[i]);

        towerModel =
            glm::scale(
                towerModel,
                glm::vec3(
                    4.0f,
                    14.0f,
                    4.0f));

        DrawMesh(
            castleTowerMesh,
            towerModel,
            view);
    }

    //--------------------------------------------------
    // Roof
    //--------------------------------------------------

    glm::mat4 roofModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                castlePosition.x,
                castlePosition.y + 10.5f,
                castlePosition.z));

    roofModel =
        glm::scale(
            roofModel,
            glm::vec3(
                18.0f,
                1.0f,
                14.0f));

    DrawMesh(
        castleRoofMesh,
        roofModel,
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

    //--------------------------------------------------
    // Ground
    //--------------------------------------------------

    DrawGround(
        view);

    //--------------------------------------------------
    // Trees
    //--------------------------------------------------

    for (const Tree& tree :
        world.GetTrees())
    {
        DrawTree(
            tree,
            view);
    }

    //--------------------------------------------------
    // Castle
    //--------------------------------------------------

    DrawCastle(
        world,
        view);

    //--------------------------------------------------
    // Door
    //--------------------------------------------------

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

    delete castleWallMesh;
    castleWallMesh = nullptr;

    delete castleTowerMesh;
    castleTowerMesh = nullptr;

    delete castleRoofMesh;
    castleRoofMesh = nullptr;
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Renderer::~Renderer()
{
    Shutdown();
}