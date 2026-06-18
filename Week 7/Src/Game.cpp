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

    //--------------------------------------------------
    // Mouse Capture
    //--------------------------------------------------

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

    camera.SetMovementSpeed(
        5.0f);

    camera.SetMouseSensitivity(
        0.1f);
}

void Game::InitializeWorld()
{
    world.Generate();
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

    HandleDoorInteraction();
}

void Game::HandleKeyboardInput(
    float deltaTime)
{
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
        !world.CheckWorldBounds(
            camera.GetPosition()))
    {
        camera.SetPosition(
            oldPosition);
    }

    if (
        world.CheckTreeCollision(
            camera.GetPosition()))
    {
        camera.SetPosition(
            oldPosition);
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
    UpdateCamera(
        deltaTime);

    UpdateWorld(
        deltaTime);
}

void Game::UpdateCamera(
    float deltaTime)
{
    (void)deltaTime;
}

void Game::UpdateWorld(
    float deltaTime)
{
    (void)deltaTime;
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
    renderer.Shutdown();
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