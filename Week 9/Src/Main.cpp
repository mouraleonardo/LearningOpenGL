#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "TreasureChest.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera camera;
TreasureChest* chest = nullptr;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

bool firstMouse = true;
bool ePressed = false;

float lastX = SCR_WIDTH * 0.5f;
float lastY = SCR_HEIGHT * 0.5f;

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !ePressed)
    {
        if (chest != nullptr)
            chest->Toggle();

        ePressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        ePressed = false;
    }
}

void MouseCallback(GLFWwindow*, double xpos, double ypos)
{
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void ScrollCallback(GLFWwindow*, double, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Erro ao iniciar GLEW\n";
        return -1;
    }

    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    Shader shader(
        "Src/Shaders/vertex.glsl",
        "Src/Shaders/fragment.glsl"
    );

    Texture texture(
        "Src/Resources/Textures/TX_TreasureChest.jpg"
    );

    // IMPORTANTE:
    // Agora o OpenGL já está inicializado.
    chest = new TreasureChest();

    chest->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window);

        chest->Update(deltaTime);

        glClearColor(0.25f, 0.35f, 0.45f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        texture.Bind(0);

        shader.SetInt("texture1", 0);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)SCR_WIDTH / SCR_HEIGHT,
            0.1f,
            100.0f
        );

        shader.SetMat4("projection", projection);
        shader.SetMat4("view", camera.GetViewMatrix());

        chest->Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete chest;

    glfwTerminate();

    return 0;
}