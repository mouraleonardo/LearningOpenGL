/*
    ============================================================
    Animated Car - OpenGL

    Author: Leonardo Moura
    Date: 6/4/2026

    Topic:
    Demonstrates 2D transformations in OpenGL, including:

        • Translation  (moving objects)
        • Rotation     (turning objects around a pivot point)
        • Scaling      (changing object size)

    The program renders an animated car composed of multiple
    meshes (body, wheels, and rims) and applies transformations
    to create motion and wheel rotation.

    Technologies:
        • OpenGL 3.3 Core Profile
        • GLFW
        • GLEW
        • GLM
        • Custom Shader, Mesh, and Renderer classes
    ============================================================
*/
// Use the static version of the GLEW library
#define GLEW_STATIC

// OpenGL Extension Wrangler Library
#include <glew.h>

// Window creation and input handling
#include <glfw3.h>

// Standard C++ libraries
#include <iostream>
#include <vector>
#include <cmath>

// Custom classes
#include "Shader.h"      // Loads and manages shaders
#include "Mesh.h"        // Stores vertex data in OpenGL buffers
#include "Renderer.h"    // Handles drawing and animation

// Mathematical constant
const float PI = 3.14159265359f;

/*
    Helper function that adds a colored triangle
    to a vertex array.

    Each vertex contains:
    x, y, z, r, g, b
*/
void AddTriangle(
    std::vector<float>& vertices,

    float x1, float y1,
    float x2, float y2,
    float x3, float y3,

    float r,
    float g,
    float b)
{
    vertices.insert(
        vertices.end(),
        {
            // Vertex 1
            x1,y1,0.0f,r,g,b,

            // Vertex 2
            x2,y2,0.0f,r,g,b,

            // Vertex 3
            x3,y3,0.0f,r,g,b
        });
}

int main()
{
    //------------------------------------------------
    // Initialize GLFW
    //------------------------------------------------

    if (!glfwInit())
        return -1;

    //------------------------------------------------
    // Request OpenGL 3.3 Core Profile
    //------------------------------------------------

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3);

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3);

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE);

    //------------------------------------------------
    // Create window
    //------------------------------------------------

    GLFWwindow* window =
        glfwCreateWindow(
            1280,           // Width
            720,            // Height
            "Animated using OpenGL Transformations", // Title
            nullptr,
            nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //------------------------------------------------
    // Make OpenGL context active
    //------------------------------------------------

    glfwMakeContextCurrent(window);

    //------------------------------------------------
    // Initialize GLEW
    //------------------------------------------------

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    //------------------------------------------------
    // Define viewport
    //------------------------------------------------

    glViewport(
        0,
        0,
        1280,
        720);

    //------------------------------------------------
    // Load vertex and fragment shaders
    //------------------------------------------------

    Shader shader(
        "Src/Shaders/vertex.glsl",
        "Src/Shaders/fragment.glsl");

    /*
        ========================================
        CAR BODY GEOMETRY
        ========================================
    */

    std::vector<float> bodyVertices;

    //------------------------------------------------
    // Body colors
    //------------------------------------------------

    const float BODY_R = 1.0f;
    const float BODY_G = 0.35f;
    const float BODY_B = 0.05f;

    //------------------------------------------------
    // Window colors
    //------------------------------------------------

    const float WINDOW_R = 0.55f;
    const float WINDOW_G = 0.70f;
    const float WINDOW_B = 0.85f;

    //------------------------------------------------
    // Headlight colors
    //------------------------------------------------

    const float LIGHT_R = 1.0f;
    const float LIGHT_G = 0.90f;
    const float LIGHT_B = 0.50f;

    //------------------------------------------------
    // Taillight colors
    //------------------------------------------------

    const float TAILLIGHT_R = 0.80f;
    const float TAILLIGHT_G = 0.00f;
    const float TAILLIGHT_B = 0.15f;

    //------------------------------------------------
    // EXHAUST PIPE colors
    //------------------------------------------------

    const float PIPE_R = 0.35f;
    const float PIPE_G = 0.35f;
    const float PIPE_B = 0.35f;

    /*
        MAIN BODY

        Rectangle made from 2 triangles.
    */

    AddTriangle(
        bodyVertices,
        -2.8f, -0.4f,
        2.2f, -0.4f,
        2.2f, 0.6f,
        BODY_R, BODY_G, BODY_B);

    AddTriangle(
        bodyVertices,
        -2.8f, -0.4f,
        2.2f, 0.6f,
        -2.8f, 0.6f,
        BODY_R, BODY_G, BODY_B);

    /*
        FRONT NOSE

        Slanted front section of the car.
    */

    AddTriangle(
        bodyVertices,
        2.2f, -0.4f,
        3.0f, -0.4f,
        2.8f, 0.6f,
        BODY_R, BODY_G, BODY_B);

    AddTriangle(
        bodyVertices,
        2.2f, -0.4f,
        2.8f, 0.6f,
        2.2f, 0.6f,
        BODY_R, BODY_G, BODY_B);

    /*
        CABIN / ROOF

        Forms the upper passenger section.
    */

    AddTriangle(
        bodyVertices,
        -1.45f, 0.60f,
        1.45f, 0.60f,
        0.90f, 1.70f,
        BODY_R, BODY_G, BODY_B);

    AddTriangle(
        bodyVertices,
        -1.45f, 0.60f,
        0.90f, 1.70f,
        -0.90f, 1.70f,
        BODY_R, BODY_G, BODY_B);

    /*
        LEFT WINDOW
    */

    AddTriangle(
        bodyVertices,
        -1.30f, 0.60f,
        -0.08f, 0.60f,
        -0.08f, 1.58f,
        WINDOW_R, WINDOW_G, WINDOW_B);

    AddTriangle(
        bodyVertices,
        -1.30f, 0.60f,
        -0.08f, 1.58f,
        -0.82f, 1.58f,
        WINDOW_R, WINDOW_G, WINDOW_B);

    /*
        RIGHT WINDOW
    */

    AddTriangle(
        bodyVertices,
        0.08f, 0.60f,
        1.30f, 0.60f,
        0.82f, 1.58f,
        WINDOW_R, WINDOW_G, WINDOW_B);

    AddTriangle(
        bodyVertices,
        0.08f, 0.60f,
        0.82f, 1.58f,
        0.08f, 1.58f,
        WINDOW_R, WINDOW_G, WINDOW_B);

    /*
        HEADLIGHT
    */

    AddTriangle(
        bodyVertices,
        2.45f, 0.12f,
        2.90f, 0.12f,
        2.84f, 0.42f,
        LIGHT_R, LIGHT_G, LIGHT_B);

    AddTriangle(
        bodyVertices,
        2.45f, 0.12f,
        2.84f, 0.42f,
        2.44f, 0.42f,
        LIGHT_R, LIGHT_G, LIGHT_B);

    /*
        TAILLIGHT
    */

    AddTriangle(
        bodyVertices,
        -2.80f, 0.18f,
        -2.50f, 0.18f,
        -2.50f, 0.48f,
        TAILLIGHT_R, TAILLIGHT_G, TAILLIGHT_B);

    AddTriangle(
        bodyVertices,
        -2.80f, 0.18f,
        -2.50f, 0.48f,
        -2.80f, 0.48f,
        TAILLIGHT_R, TAILLIGHT_G, TAILLIGHT_B);

    /*
        EXHAUST PIPE
    */

    AddTriangle(
        bodyVertices,
        -2.85f, -0.52f,   // left and lower
        -2.60f, -0.52f,   // left and lower
        -2.60f, -0.34f,
        PIPE_R, PIPE_G, PIPE_B);

    AddTriangle(
        bodyVertices,
        -2.85f, -0.52f,
        -2.60f, -0.34f,
        -2.85f, -0.34f,
        PIPE_R, PIPE_G, PIPE_B);


    /*
        ========================================
        WHEEL GEOMETRY
        ========================================

        Creates a circle using triangle fan logic.

        40 triangles approximate a wheel.
    */

    std::vector<float> wheelVertices;

    const float TIRE_R = 0.05f;
    const float TIRE_G = 0.05f;
    const float TIRE_B = 0.05f;

    const int SEGMENTS = 40;
    const float radius = 0.55f;

    for (int i = 0; i < SEGMENTS; i++)
    {
        // Current angle
        float a1 =
            (float)i /
            SEGMENTS *
            2.0f *
            PI;

        // Next angle
        float a2 =
            (float)(i + 1) /
            SEGMENTS *
            2.0f *
            PI;

        // Triangle from center to circle edge
        AddTriangle(
            wheelVertices,

            0.0f, 0.0f,

            cos(a1) * radius,
            sin(a1) * radius,

            cos(a2) * radius,
            sin(a2) * radius,

            TIRE_R,
            TIRE_G,
            TIRE_B);
    }

    /*
        ========================================
        STAR / RIM GEOMETRY
        ========================================

        Creates 5 spokes inside the wheel.
    */

    std::vector<float> starVertices;

    const float RIM_R = 0.85f;
    const float RIM_G = 0.85f;
    const float RIM_B = 0.85f;

    for (int i = 0; i < 5; i++)
    {
        // Center angle of current spoke
        float a =
            i *
            2.0f *
            PI /
            5.0f;

        // Left edge of spoke
        float left =
            a - 0.15f;

        // Right edge of spoke
        float right =
            a + 0.15f;

        // Triangle spoke
        AddTriangle(
            starVertices,

            0.0f,
            0.0f,

            cos(left) * 0.45f,
            sin(left) * 0.45f,

            cos(right) * 0.45f,
            sin(right) * 0.45f,

            RIM_R,
            RIM_G,
            RIM_B);
    }

    /*
        Smoke particles are rendered as circles.

        During animation the particles:
        - move away from the exhaust (translation)
        - grow in size (scaling)

        This demonstrates scaling in a visually meaningful way.
    */

    /*
        ========================================
        SMOKE GEOMETRY
        ========================================
    */

    std::vector<float> smokeVertices;

    const float SMOKE_R = 0.65f;
    const float SMOKE_G = 0.65f;
    const float SMOKE_B = 0.65f;

    const float smokeRadius = 0.25f;

    for (int i = 0; i < SEGMENTS; i++)
    {
        float a1 =
            (float)i /
            SEGMENTS *
            2.0f *
            PI;

        float a2 =
            (float)(i + 1) /
            SEGMENTS *
            2.0f *
            PI;

        AddTriangle(
            smokeVertices,

            0.0f, 0.0f,

            cos(a1) * smokeRadius,
            sin(a1) * smokeRadius,

            cos(a2) * smokeRadius,
            sin(a2) * smokeRadius,

            SMOKE_R,
            SMOKE_G,
            SMOKE_B);
    }

    /*
        Upload geometry to GPU
    */

    Mesh bodyMesh(bodyVertices);
    Mesh wheelMesh(wheelVertices);
    Mesh starMesh(starVertices);
    Mesh smokeMesh(smokeVertices);

    /*
        Renderer receives:
        - Shader
        - Car body mesh
        - Wheel mesh
        - Rim mesh
    */

    Renderer renderer(
        &shader,
        &bodyMesh,
        &wheelMesh,
        &starMesh,
        &smokeMesh);

    /*
        ========================================
        MAIN LOOP
        ========================================
    */

    while (!glfwWindowShouldClose(window))
    {
        //------------------------------------------------
        // Clear screen to black
        //------------------------------------------------

        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f);

        glClear(
            GL_COLOR_BUFFER_BIT);

        //------------------------------------------------
        // ESC closes window
        //------------------------------------------------

        if (glfwGetKey(
            window,
            GLFW_KEY_ESCAPE) ==
            GLFW_PRESS)
        {
            glfwSetWindowShouldClose(
                window,
                true);
        }

        //------------------------------------------------
        // Get elapsed time
        //------------------------------------------------

        float time =
            static_cast<float>(
                glfwGetTime());

        //------------------------------------------------
        // Draw animated car
        //------------------------------------------------

        renderer.Render(time);

        //------------------------------------------------
        // Present frame
        //------------------------------------------------

        glfwSwapBuffers(window);

        //------------------------------------------------
        // Process keyboard/mouse events
        //------------------------------------------------

        glfwPollEvents();
    }

    //------------------------------------------------
    // Cleanup
    //------------------------------------------------

    glfwTerminate();

    return 0;
}