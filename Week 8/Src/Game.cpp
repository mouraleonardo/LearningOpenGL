#include "Game.h"

#include <glm.hpp>

Game::Game(
    GLFWwindow* gameWindow,
    int width,
    int height)
{
    //--------------------------------------------------
    // Window
    //--------------------------------------------------

    window =
        gameWindow;

    screenWidth =
        width;

    screenHeight =
        height;

    //--------------------------------------------------
    // Mouse
    //--------------------------------------------------

    firstMouse =
        true;

    lastMouseX =
        static_cast<float>(
            width) * 0.5f;

    lastMouseY =
        static_cast<float>(
            height) * 0.5f;
}

//--------------------------------------------------
// Initialization
//--------------------------------------------------

bool Game::Initialize(
    Shader* shader)
{
    renderer.SetShader(
        shader);

    if (!renderer.Initialize(
        screenWidth,
        screenHeight))
    {
        return false;
    }

    InitializeCamera();

    InitializeWorld();

    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED);

    return true;
}

void Game::InitializeCamera()
{
    camera.SetPosition(
        {
            0.0f,
            1.8f,
            0.0f
        });

    //--------------------------------------------------
    // Walk
    //--------------------------------------------------

    camera.SetWalkSpeed(
        5.0f);

    //--------------------------------------------------
    // Sprint
    //--------------------------------------------------

    camera.SetSprintSpeed(
        20.0f);

    //--------------------------------------------------
    // Mouse
    //--------------------------------------------------

    camera.SetMouseSensitivity(
        0.1f);

    //--------------------------------------------------
    // Physics
    //--------------------------------------------------

    camera.SetGravity(
        20.0f);

    camera.SetJumpForce(
        8.0f);

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    camera.SetPlayerRadius(
        0.4f);

    camera.SetPlayerHeight(
        1.8f);
}

void Game::InitializeWorld()
{
    world.Generate();

    world.SetPlayerRadius(
        camera.GetPlayerRadius());
}

//--------------------------------------------------
// Input
//--------------------------------------------------

void Game::ProcessInput(
    float deltaTime)
{
    HandleKeyboardInput(
        deltaTime);

    HandleMouseInput();

    HandleJumpInput();

    HandleDoorInteraction();
}

void Game::HandleKeyboardInput(
    float deltaTime)
{
    //--------------------------------------------------
    // Sprint
    //--------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_LEFT_SHIFT)
        ==
        GLFW_PRESS)
    {
        camera.StartSprint();
    }
    else
    {
        camera.StopSprint();
    }

    //--------------------------------------------------
    // Save Position
    //--------------------------------------------------

    glm::vec3 oldPosition =
        camera.GetPosition();

    //--------------------------------------------------
    // W
    //--------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_W)
        ==
        GLFW_PRESS)
    {
        camera.MoveForward(
            deltaTime);
    }

    //--------------------------------------------------
    // S
    //--------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_S)
        ==
        GLFW_PRESS)
    {
        camera.MoveBackward(
            deltaTime);
    }

    //--------------------------------------------------
    // A
    //--------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_A)
        ==
        GLFW_PRESS)
    {
        camera.MoveLeft(
            deltaTime);
    }

    //--------------------------------------------------
    // D
    //--------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_D)
        ==
        GLFW_PRESS)
    {
        camera.MoveRight(
            deltaTime);
    }

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    if (
        world.CheckCollision(
            camera.GetPosition()))
    {
        camera.SetPosition(
            oldPosition);
    }
}

void Game::HandleJumpInput()
{
    static bool keyReleased =
        true;

    if (
        glfwGetKey(
            window,
            GLFW_KEY_SPACE)
        ==
        GLFW_RELEASE)
    {
        keyReleased =
            true;
    }

    if (
        glfwGetKey(
            window,
            GLFW_KEY_SPACE)
        ==
        GLFW_PRESS
        &&
        keyReleased)
    {
        keyReleased =
            false;

        camera.Jump();
    }
}

void Game::HandleMouseInput()
{
    double mouseX;
    double mouseY;

    glfwGetCursorPos(
        window,
        &mouseX,
        &mouseY);

    if (firstMouse)
    {
        lastMouseX =
            static_cast<float>(
                mouseX);

        lastMouseY =
            static_cast<float>(
                mouseY);

        firstMouse =
            false;
    }

    float xOffset =
        static_cast<float>(
            mouseX)
        -
        lastMouseX;

    float yOffset =
        lastMouseY
        -
        static_cast<float>(
            mouseY);

    lastMouseX =
        static_cast<float>(
            mouseX);

    lastMouseY =
        static_cast<float>(
            mouseY);

    camera.ProcessMouseMovement(
        xOffset,
        yOffset);
}

void Game::HandleDoorInteraction()
{
    static bool keyReleased =
        true;

    if (
        glfwGetKey(
            window,
            GLFW_KEY_E)
        ==
        GLFW_RELEASE)
    {
        keyReleased =
            true;
    }

    if (
        glfwGetKey(
            window,
            GLFW_KEY_E)
        ==
        GLFW_PRESS
        &&
        keyReleased)
    {
        keyReleased =
            false;

        //--------------------------------------------------
        // Treasure Chest
        //--------------------------------------------------

        TreasureChest* chest =
            world.GetInteractableTreasureChest(
                camera.GetPosition());

        if (chest != nullptr)
        {
            chest->Toggle();
            return;
        }

        //--------------------------------------------------
        // Door
        //--------------------------------------------------

        if (
            world.CanInteractWithDoor(
                camera.GetPosition()))
        {
            world.GetDoor().
                Toggle();
        }
    }
}

//--------------------------------------------------
// Update
//--------------------------------------------------

void Game::Update(
    float deltaTime)
{
    UpdatePhysics(
        deltaTime);

    UpdateCamera(
        deltaTime);

    UpdateWorld(
        deltaTime);
}

void Game::UpdatePhysics(
    float deltaTime)
{
    //--------------------------------------------------
    // Previous Position
    //--------------------------------------------------

    glm::vec3 previousPosition =
        camera.GetPosition();

    //--------------------------------------------------
    // Gravity
    //--------------------------------------------------

    camera.ApplyGravity(
        deltaTime);

    //--------------------------------------------------
    // Collision
    //--------------------------------------------------

    if (
        world.CheckCollision(
            camera.GetPosition()))
    {
        camera.SetPosition(
            previousPosition);
    }

    //--------------------------------------------------
    // Flat Terrain
    //--------------------------------------------------

    glm::vec3 position =
        camera.GetPosition();

    float terrainHeight =
        world.GetHeightAt(
            position.x,
            position.z);

    if (
        position.y
        <=
        terrainHeight +
        camera.GetPlayerHeight())
    {
        camera.Land(
            terrainHeight);
    }
}

void Game::UpdateCamera(
    float deltaTime)
{
    (void)deltaTime;

    glm::vec3 position =
        camera.GetPosition();

    float terrainHeight =
        world.GetHeightAt(
            position.x,
            position.z);

    if (
        camera.IsGrounded())
    {
        position.y =
            terrainHeight +
            camera.GetPlayerHeight();

        camera.SetPosition(
            position);
    }
}

void Game::UpdateWorld(
    float deltaTime)
{
    //--------------------------------------------------
    // Door
    //--------------------------------------------------

    world.GetDoor().Update(
        deltaTime);

    //--------------------------------------------------
    // Treasure Chests
    //--------------------------------------------------

    for (
        TreasureChest& chest :
        world.GetTreasureChests())
    {
        chest.Update(
            deltaTime);
    }
}

//--------------------------------------------------
// Render
//--------------------------------------------------

void Game::Render()
{
    renderer.BeginFrame();

    renderer.RenderWorld(
        world,
        camera);

    renderer.EndFrame();
}

//--------------------------------------------------
// Shutdown
//--------------------------------------------------

void Game::Shutdown()
{
}

//--------------------------------------------------
// Accessors
//--------------------------------------------------

Camera& Game::GetCamera()
{
    return camera;
}

World& Game::GetWorld()
{
    return world;
}

Renderer& Game::GetRenderer()
{
    return renderer;
}

//--------------------------------------------------
// Destructor
//--------------------------------------------------

Game::~Game()
{
}