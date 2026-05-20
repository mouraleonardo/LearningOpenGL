// ==========================================================
// Modern OpenGL OOP Rotating RGB Triangle
//
// Uses:
// GLFW
// GLEW
// OpenGL 3.3 Core
//
// Demonstrates:
// 1. OOP Design
// 2. Shader Class
// 3. Triangle Class
// 4. VAO + VBO
// 5. RGB Vertex Colors
// 6. 3D Rotation
// ==========================================================

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <cmath>

using namespace std;

// ==========================================================
// Shader Class
// ==========================================================
class Shader
{
private:

    unsigned int shaderProgram;

public:

    // ======================================================
    // Constructor
    // ======================================================
    Shader(const char* vertexSource,
        const char* fragmentSource)
    {
        // ==================================================
        // Create Vertex Shader
        // ==================================================
        unsigned int vertexShader;

        vertexShader =
            glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(
            vertexShader,
            1,
            &vertexSource,
            NULL
        );

        glCompileShader(vertexShader);

        // ==================================================
        // Create Fragment Shader
        // ==================================================
        unsigned int fragmentShader;

        fragmentShader =
            glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(
            fragmentShader,
            1,
            &fragmentSource,
            NULL
        );

        glCompileShader(fragmentShader);

        // ==================================================
        // Create Shader Program
        // ==================================================
        shaderProgram = glCreateProgram();

        glAttachShader(
            shaderProgram,
            vertexShader
        );

        glAttachShader(
            shaderProgram,
            fragmentShader
        );

        glLinkProgram(shaderProgram);

        // ==================================================
        // Delete Shader Objects
        // ==================================================
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // ======================================================
    // Activate Shader
    // ======================================================
    void use()
    {
        glUseProgram(shaderProgram);
    }

    // ======================================================
    // Get Shader Program ID
    // ======================================================
    unsigned int getID()
    {
        return shaderProgram;
    }
};

// ==========================================================
// Triangle Class
// ==========================================================
class Triangle
{
private:

    unsigned int VAO;
    unsigned int VBO;

public:

    // ======================================================
    // Constructor
    // ======================================================
    Triangle()
    {
        // ==================================================
        // Vertex Data
        //
        // X     Y     Z      R     G     B
        // ==================================================
        float vertices[] =
        {
            -0.5f, -0.5f, 0.0f,
             1.0f,  0.0f, 0.0f,

             0.0f,  0.5f, 0.0f,
             0.0f,  1.0f, 0.0f,

             0.5f, -0.5f, 0.0f,
             0.0f,  0.0f, 1.0f
        };

        // ==================================================
        // Generate VAO + VBO
        // ==================================================
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // ==================================================
        // Bind VAO
        // ==================================================
        glBindVertexArray(VAO);

        // ==================================================
        // Bind VBO
        // ==================================================
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // ==================================================
        // Send Data to GPU
        // ==================================================
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
        );

        // ==================================================
        // Position Attribute
        // ==================================================
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)0
        );

        glEnableVertexAttribArray(0);

        // ==================================================
        // Color Attribute
        // ==================================================
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)(3 * sizeof(float))
        );

        glEnableVertexAttribArray(1);
    }

    // ======================================================
    // Draw Triangle
    // ======================================================
    void draw()
    {
        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );
    }
};

// ==========================================================
// Vertex Shader Source
// ==========================================================
const char* vertexShaderSource = R"(

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 rotation;

void main()
{
    gl_Position =
        rotation *
        vec4(aPos, 1.0);

    vertexColor = aColor;
}

)";

// ==========================================================
// Fragment Shader Source
// ==========================================================
const char* fragmentShaderSource = R"(

#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor =
        vec4(vertexColor, 1.0);
}

)";

// ==========================================================
// Main
// ==========================================================
int main()
{
    // ======================================================
    // Initialize GLFW
    // ======================================================
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW"
            << endl;

        return -1;
    }

    // ======================================================
    // OpenGL Version
    // ======================================================
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

    // ======================================================
    // Create Window
    // ======================================================
    GLFWwindow* window =
        glfwCreateWindow(
            800,
            600,
            "OOP Rotating RGB Triangle",
            NULL,
            NULL
        );

    if (!window)
    {
        cout << "Failed to create window"
            << endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    // ======================================================
    // Initialize GLEW
    // ======================================================
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW"
            << endl;

        return -1;
    }

    // ======================================================
    // Print OpenGL Version
    // ======================================================
    cout << "OpenGL Version: "
        << glGetString(GL_VERSION)
        << endl;

    // ======================================================
    // Create Shader Object
    // ======================================================
    Shader shader(
        vertexShaderSource,
        fragmentShaderSource
    );

    // ======================================================
    // Create Triangle Object
    // ======================================================
    Triangle triangle;

    // ======================================================
    // Main Render Loop
    // ======================================================
    while (!glfwWindowShouldClose(window))
    {
        // ==================================================
        // Clear Screen
        // ==================================================
        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        // ==================================================
        // Use Shader
        // ==================================================
        shader.use();

        // ==================================================
        // Rotation
        // ==================================================
        float angle =
            (float)glfwGetTime();

        float cosA = cos(angle);
        float sinA = sin(angle);

        // ==================================================
        // Rotation Matrix
        // ==================================================
        float rotationMatrix[] =
        {
             cosA,  sinA, 0.0f, 0.0f,
            -sinA,  cosA, 0.0f, 0.0f,
             0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.0f, 0.0f, 1.0f
        };

        // ==================================================
        // Send Matrix to Shader
        // ==================================================
        unsigned int rotationLocation =
            glGetUniformLocation(
                shader.getID(),
                "rotation"
            );

        glUniformMatrix4fv(
            rotationLocation,
            1,
            GL_FALSE,
            rotationMatrix
        );

        // ==================================================
        // Draw Triangle
        // ==================================================
        triangle.draw();

        // ==================================================
        // Swap Buffers
        // ==================================================
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // ======================================================
    // Shutdown GLFW
    // ======================================================
    glfwTerminate();

    return 0;
}