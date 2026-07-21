/*
    ============================================================
    Treasure Chest - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This application demonstrates the fundamentals of modern
    OpenGL by rendering an interactive 3D Treasure Chest.

    The project initializes an OpenGL rendering context,
    loads shaders and textures, creates a first-person camera,
    and renders a textured 3D object inside the main game loop.

    The application also demonstrates basic interaction by
    allowing the player to open and close the treasure chest
    using the keyboard.

    Features:

        • OpenGL initialization
        • GLFW window creation
        • GLEW initialization
        • Shader loading
        • Texture loading
        • First Person Camera (FPS)
        • Mouse Look
        • Perspective Projection
        • Delta Time movement
        • Keyboard input processing
        • Interactive Treasure Chest
        • Depth Testing
        • Game Loop

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLFW
        • GLEW
        • GLM
        • stb_image
        • C++

    Learning Topics:

        • Rendering Pipeline
        • Window Management
        • OpenGL Context Creation
        • Camera Systems
        • Model / View / Projection Matrices
        • Texture Mapping
        • Shader Programming
        • User Input
        • Real-Time Rendering
        • Game Loop Architecture

    ============================================================
*/

#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "TreasureChest.h"

//
// Window dimensions.
//
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//
// Global camera used throughout the application.
//
Camera camera;

//
// Pointer to the treasure chest object.
//
// The object is created only after OpenGL has been fully
// initialized because it creates GPU resources (VAOs/VBOs).
//
TreasureChest* chest = nullptr;

//
// Timing variables used for frame-independent movement.
//
float lastFrame = 0.0f;
float deltaTime = 0.0f;

//
// Variables used by the Mouse Look system.
//
bool firstMouse = true;

float lastX = SCR_WIDTH * 0.5f;
float lastY = SCR_HEIGHT * 0.5f;

//
// Prevents multiple key presses while holding E.
//
bool ePressed = false;

//
//--------------------------------------------------------------
// Processes keyboard input every frame.
//--------------------------------------------------------------
//
void ProcessInput(GLFWwindow* window)
{
    //
    // Close the application.
    //
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //
    // Camera movement.
    //
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //
    // Toggle the treasure chest.
    //
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !ePressed)
    {
        if (chest != nullptr)
            chest->Toggle();

        ePressed = true;
    }

    //
    // Wait until the key is released before allowing
    // another toggle operation.
    //
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        ePressed = false;
    }
}

//
//--------------------------------------------------------------
// Mouse callback.
//
// Updates the camera orientation based on the mouse movement.
//--------------------------------------------------------------
//
void MouseCallback(GLFWwindow*, double xpos, double ypos)
{
    //
    // Ignore the first mouse movement to avoid
    // a sudden camera jump.
    //
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;

        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(
        xoffset,
        yoffset
    );
}

//
//--------------------------------------------------------------
// Mouse wheel callback.
//
// Controls the camera zoom.
//--------------------------------------------------------------
//
void ScrollCallback(
    GLFWwindow*,
    double,
    double yoffset)
{
    camera.ProcessMouseScroll(
        (float)yoffset
    );
}

int main()
{
    //----------------------------------------------------------
    // Initialize GLFW.
    //----------------------------------------------------------

    if (!glfwInit())
        return -1;

    //----------------------------------------------------------
    // Configure the OpenGL version and profile.
    //----------------------------------------------------------

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    //----------------------------------------------------------
    // Create the application window.
    //----------------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Treasure Chest",
        nullptr,
        nullptr
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //----------------------------------------------------------
    // Make the OpenGL context current.
    //----------------------------------------------------------

    glfwMakeContextCurrent(window);

    //----------------------------------------------------------
    // Initialize GLEW.
    //----------------------------------------------------------

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout
            << "Failed to initialize GLEW."
            << std::endl;

        return -1;
    }

    //----------------------------------------------------------
    // Register input callbacks.
    //----------------------------------------------------------

    glfwSetCursorPosCallback(
        window,
        MouseCallback
    );

    glfwSetScrollCallback(
        window,
        ScrollCallback
    );

    //----------------------------------------------------------
    // Hide and capture the mouse cursor.
    //----------------------------------------------------------

    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED
    );

    //----------------------------------------------------------
    // Configure the viewport.
    //----------------------------------------------------------

    glViewport(
        0,
        0,
        SCR_WIDTH,
        SCR_HEIGHT
    );

    //----------------------------------------------------------
    // Enable depth testing.
    //----------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    //----------------------------------------------------------
    // Load shaders.
    //----------------------------------------------------------

    Shader shader(
        "Src/Shaders/vertex.glsl",
        "Src/Shaders/fragment.glsl"
    );

    //----------------------------------------------------------
    // Load the treasure chest texture.
    //----------------------------------------------------------

    Texture texture(
        "Src/Resources/Textures/TX_TreasureChest.jpg"
    );

    //----------------------------------------------------------
    // Create the treasure chest.
    //
    // This must happen after OpenGL initialization because
    // the constructor creates GPU resources.
    //----------------------------------------------------------

    chest = new TreasureChest();

    chest->SetPosition(
        glm::vec3(
            0.0f,
            0.0f,
            0.0f
        )
    );

    //----------------------------------------------------------
    // Main Render Loop.
    //----------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        //
        // Calculate delta time.
        //
        float currentFrame =
            (float)glfwGetTime();

        deltaTime =
            currentFrame - lastFrame;

        lastFrame =
            currentFrame;

        //
        // Process user input.
        //
        ProcessInput(window);

        //
        // Update animated objects.
        //
        chest->Update(deltaTime);

        //
        // Clear the frame.
        //
        glClearColor(
            0.25f,
            0.35f,
            0.45f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        //
        // Activate the shader program.
        //
        shader.Use();

        //
        // Bind the texture.
        //
        texture.Bind(0);

        shader.SetInt(
            "texture1",
            0
        );

        // Phong lighting parameters consumed by fragment.glsl.
        // lightPos and viewPos are in world space, matching FragPos and
        // Normal produced by vertex.glsl. The warm light emphasizes the
        // wooden texture and the new internal walls.
        shader.SetVec3("lightPos", glm::vec3(2.5f, 3.5f, 3.0f));
        shader.SetVec3("lightColor", glm::vec3(1.0f, 0.92f, 0.78f));
        // Luz Phong secundária: alcança as faces opostas à luz principal.
        shader.SetVec3("fillLightPos", glm::vec3(-3.0f, 2.0f, -2.5f));
        shader.SetVec3("fillLightColor", glm::vec3(0.22f, 0.28f, 0.38f));
        shader.SetVec3("viewPos", camera.Position);
        shader.SetFloat("ambientStrength", 0.16f);  // indirect/minimum light
        shader.SetFloat("specularStrength", 0.32f); // highlight intensity
        shader.SetFloat("shininess", 32.0f);        // highlight concentration
        // Contorno dourado suave: valor baixo para destacar a forma fechada
        // sem substituir as componentes Phong principais.
        shader.SetFloat("rimStrength", 0.12f);
        shader.SetVec3("rimColor", glm::vec3(1.0f, 0.55f, 0.16f));
        // Escurece a madeira, preservando o contraste criado pelas luzes.
        shader.SetFloat("exposure", 0.58f);

        //
        // Create the Projection Matrix.
        //
        glm::mat4 projection =
            glm::perspective(
                glm::radians(camera.Zoom),
                (float)SCR_WIDTH / SCR_HEIGHT,
                0.1f,
                100.0f
            );

        shader.SetMat4(
            "projection",
            projection
        );

        //
        // Send the View Matrix.
        //
        shader.SetMat4(
            "view",
            camera.GetViewMatrix()
        );

        //
        // Render the treasure chest.
        //
        chest->Draw(shader);

        //
        // Display the rendered frame.
        //
        glfwSwapBuffers(window);

        //
        // Process window events.
        //
        glfwPollEvents();
    }

    //----------------------------------------------------------
    // Release allocated memory.
    //----------------------------------------------------------

    delete chest;

    //----------------------------------------------------------
    // Shutdown GLFW.
    //----------------------------------------------------------

    glfwTerminate();

    return 0;
}
