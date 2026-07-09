/*
    ============================================================
    FPS Explorer - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This application implements a first-person 3D exploration
    environment using modern OpenGL.

    The project demonstrates:

        • OpenGL initialization
        • Window and context creation
        • Shader management
        • Game loop architecture
        • Delta time based updates
        • First Person Camera (FPS)
        • Perspective Projection
        • View Matrix generation
        • Mouse Look controls
        • Sprint movement
        • Gravity simulation
        • Jump mechanics
        • Collision detection
        • Open world navigation
        • Interactive castle door system
        • Basic world rendering

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLFW
        • GLEW
        • GLM
        • C++

    Learning Topics:

        • Coordinate Systems
        • Model Matrices
        • View Matrices
        • Projection Matrices
        • Camera Systems
        • Real-Time Rendering
        • Input Processing
        • Physics Fundamentals

    ============================================================
*/

#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Game.h"

//--------------------------------------------------
// Fixed application resolution.
//
// The entire world is rendered using
// a 1280x720 viewport.
//--------------------------------------------------

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

int main()
{
    //--------------------------------------------------
    // Initialize GLFW.
    //
    // GLFW is responsible for:
    //
    //  • Window creation
    //  • OpenGL context creation
    //  • Keyboard input
    //  • Mouse input
    //  • Event processing
    //--------------------------------------------------

    if (!glfwInit())
    {
        std::cout
            << "Failed to initialize GLFW"
            << std::endl;

        return -1;
    }

    //--------------------------------------------------
    // Configure OpenGL.
    //
    // Using:
    //
    //      OpenGL 3.3 Core Profile
    //
    // Core Profile removes legacy
    // functionality and enforces
    // modern OpenGL practices.
    //--------------------------------------------------

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3);

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3);

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE);

    //--------------------------------------------------
    // Create application window.
    //
    // Parameters:
    //
    //  Width
    //  Height
    //  Window Title
    //  Monitor
    //  Shared Context
    //--------------------------------------------------

    GLFWwindow* window =
        glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            "FPS Explorer",
            nullptr,
            nullptr);

    //--------------------------------------------------
    // Verify successful window creation.
    //--------------------------------------------------

    if (!window)
    {
        std::cout
            << "Failed to create window"
            << std::endl;

        glfwTerminate();

        return -1;
    }

    //--------------------------------------------------
    // Make this window's OpenGL context
    // the active context.
    //--------------------------------------------------

    glfwMakeContextCurrent(
        window);

    //--------------------------------------------------
    // Initialize GLEW.
    //
    // GLEW loads modern OpenGL functions.
    //
    // Examples:
    //
    //      glCreateShader()
    //      glCreateProgram()
    //      glGenVertexArrays()
    //      glBindVertexArray()
    //
    // Without GLEW these functions
    // would not be available.
    //--------------------------------------------------

    glewExperimental =
        GL_TRUE;

    GLenum result =
        glewInit();

    //--------------------------------------------------
    // Verify successful GLEW initialization.
    //--------------------------------------------------

    if (result != GLEW_OK)
    {
        std::cout
            << "GLEW ERROR: "
            << glewGetErrorString(
                result)
            << std::endl;

        glfwDestroyWindow(
            window);

        glfwTerminate();

        return -1;
    }

    //--------------------------------------------------
    // Configure OpenGL rendering state.
    //
    // Viewport:
    // Defines the drawable area.
    //
    // Depth Testing:
    // Ensures closer objects appear
    // in front of distant objects.
    //
    // Required for rendering:
    //
    //  • Terrain
    //  • Trees
    //  • Castle
    //  • Door
    //--------------------------------------------------

    glViewport(
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT);

    glEnable(
        GL_DEPTH_TEST);

    //--------------------------------------------------
    // Load and compile shader program.
    //
    // Vertex Shader:
    // Transforms vertices through the
    // rendering pipeline.
    //
    // Fragment Shader:
    // Computes the final pixel color.
    //--------------------------------------------------

    Shader shader(
        "Src/Shaders/vertex.glsl",
        "Src/Shaders/fragment.glsl");

    //--------------------------------------------------
    // Create main game controller.
    //
    // The Game class manages:
    //
    //  • World generation
    //  • Camera system
    //  • Input processing
    //  • Physics simulation
    //  • Collision detection
    //  • Rendering pipeline
    //  • Interactive objects
    //--------------------------------------------------

    Game game(
        window,
        WINDOW_WIDTH,
        WINDOW_HEIGHT);

    //--------------------------------------------------
    // Initialize all game systems.
    //
    // Includes:
    //
    //  • Renderer initialization
    //  • Camera setup
    //  • World generation
    //  • Object creation
    //  • Shader configuration
    //--------------------------------------------------

    if (!game.Initialize(
        &shader))
    {
        std::cout
            << "Failed to initialize game"
            << std::endl;

        glfwDestroyWindow(
            window);

        glfwTerminate();

        return -1;
    }

    //--------------------------------------------------
    // Store initial timestamp.
    //
    // Used for delta time calculations.
    //
    // Delta time allows movement and
    // simulation to remain independent
    // of frame rate.
    //--------------------------------------------------

    float lastTime =
        static_cast<float>(
            glfwGetTime());

    //--------------------------------------------------
    // Main Application Loop.
    //
    // Every frame performs:
    //
    //  1. Process Input
    //  2. Update World
    //  3. Render Scene
    //  4. Present Frame
    //
    // This architecture is used by
    // most commercial game engines.
    //--------------------------------------------------

    while (
        !glfwWindowShouldClose(
            window))
    {
        //--------------------------------------------------
        // Current frame time.
        //--------------------------------------------------

        float currentTime =
            static_cast<float>(
                glfwGetTime());

        //--------------------------------------------------
        // Compute delta time.
        //
        // Delta Time =
        //
        // Current Time
        //      -
        // Previous Time
        //
        // Produces frame-rate independent
        // movement and physics.
        //--------------------------------------------------

        float deltaTime =
            currentTime -
            lastTime;

        lastTime =
            currentTime;

        //--------------------------------------------------
        // Allow application exit.
        //
        // ESC closes the application.
        //--------------------------------------------------

        if (
            glfwGetKey(
                window,
                GLFW_KEY_ESCAPE)
            ==
            GLFW_PRESS)
        {
            glfwSetWindowShouldClose(
                window,
                GLFW_TRUE);
        }

        //--------------------------------------------------
        // Process user input.
        //
        // Examples:
        //
        //  • WASD movement
        //  • Mouse look
        //  • Sprint
        //  • Jump
        //  • Door interaction
        //--------------------------------------------------

        game.ProcessInput(
            deltaTime);

        //--------------------------------------------------
        // Update game systems.
        //
        // Includes:
        //
        //  • Camera update
        //  • Physics update
        //  • Gravity
        //  • Collision detection
        //  • Object animation
        //--------------------------------------------------

        game.Update(
            deltaTime);

        //--------------------------------------------------
        // Render current frame.
        //
        // Draws:
        //
        //  • Terrain
        //  • Trees
        //  • Castle
        //  • Door
        //  • World geometry
        //
        // Rendering uses:
        //
        //      Model Matrix
        //              ↓
        //      View Matrix
        //              ↓
        //   Projection Matrix
        //--------------------------------------------------

        game.Render();

        //--------------------------------------------------
        // Present rendered image.
        //
        // Double buffering prevents
        // flickering and tearing.
        //--------------------------------------------------

        glfwSwapBuffers(
            window);

        //--------------------------------------------------
        // Process operating system events.
        //
        // Examples:
        //
        //  • Keyboard input
        //  • Mouse movement
        //  • Window events
        //  • Close requests
        //--------------------------------------------------

        glfwPollEvents();
    }

    //--------------------------------------------------
    // Shutdown game systems.
    //
    // Release all allocated resources.
    //--------------------------------------------------

    game.Shutdown();

    //--------------------------------------------------
    // Destroy application window.
    //--------------------------------------------------

    glfwDestroyWindow(
        window);

    //--------------------------------------------------
    // Shutdown GLFW.
    //--------------------------------------------------

    glfwTerminate();

    //--------------------------------------------------
    // Exit successfully.
    //--------------------------------------------------

    return 0;
}
