#ifndef GAME_H
#define GAME_H

#include <glew.h>
#include <glfw3.h>

#include "Camera.h"
#include "World.h"
#include "Renderer.h"
#include "Shader.h"

class Game
{
private:

    //--------------------------------------------------
    // Window
    //--------------------------------------------------

    GLFWwindow* window;

    int screenWidth;

    int screenHeight;

    //--------------------------------------------------
    // Systems
    //--------------------------------------------------

    Renderer renderer;

    World world;

    Camera camera;

    //--------------------------------------------------
    // Mouse
    //--------------------------------------------------

    bool firstMouse;

    float lastMouseX;

    float lastMouseY;

private:

    //--------------------------------------------------
    // Initialization
    //--------------------------------------------------

    void InitializeCamera();

    void InitializeWorld();

    //--------------------------------------------------
    // Input
    //--------------------------------------------------

    void HandleKeyboardInput(
        float deltaTime);

    void HandleMouseInput();

    void HandleJumpInput();

    void HandleDoorInteraction();

    //--------------------------------------------------
    // Physics
    //--------------------------------------------------

    void UpdatePhysics(
        float deltaTime);

    void UpdateCamera(
        float deltaTime);

    void UpdateWorld(
        float deltaTime);

public:

    //--------------------------------------------------
    // Constructor
    //--------------------------------------------------

    Game(
        GLFWwindow* gameWindow,
        int width,
        int height);

    //--------------------------------------------------
    // Initialization
    //--------------------------------------------------

    bool Initialize(
        Shader* shader);

    //--------------------------------------------------
    // Main Loop
    //--------------------------------------------------

    void ProcessInput(
        float deltaTime);

    void Update(
        float deltaTime);

    void Render();

    //--------------------------------------------------
    // Shutdown
    //--------------------------------------------------

    void Shutdown();

    //--------------------------------------------------
    // Accessors
    //--------------------------------------------------

    Camera& GetCamera();

    World& GetWorld();

    Renderer& GetRenderer();

    //--------------------------------------------------
    // Destructor
    //--------------------------------------------------

    ~Game();
};

#endif