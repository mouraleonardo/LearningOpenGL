// ==========================================================
// Pong Game With Score System
// OpenGL + GLFW + GLEW
// First to 10 wins
// ==========================================================

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <string>

using namespace std;

// ==========================================================
// Window
// ==========================================================
const int WIDTH = 800;
const int HEIGHT = 600;

// ==========================================================
// Paddle settings
// ==========================================================
float paddleWidth = 0.03f;
float paddleHeight = 0.25f;

float leftPaddleX = -0.9f;
float rightPaddleX = 0.9f;

float leftPaddleY = 0.0f;
float rightPaddleY = 0.0f;

float paddleSpeed = 0.02f;

// ==========================================================
// Ball settings
// ==========================================================
float ballX = 0.0f;
float ballY = 0.0f;

float ballSize = 0.03f;

float ballSpeedX = 0.01f;
float ballSpeedY = 0.008f;

// ==========================================================
// Score
// ==========================================================
int leftScore = 0;
int rightScore = 0;

bool gameOver = false;

string winnerText = "";

// ==========================================================
// Vertex Shader
// ==========================================================
const char* vertexShaderSource = R"(

#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 offset;
uniform vec2 scale;

void main()
{
    vec2 pos = aPos * scale + offset;

    gl_Position = vec4(pos, 0.0, 1.0);
}

)";

// ==========================================================
// Fragment Shader
// ==========================================================
const char* fragmentShaderSource = R"(

#version 330 core

out vec4 FragColor;

uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0);
}

)";

// ==========================================================
// Create shader
// ==========================================================
unsigned int createShader(unsigned int type,
                          const char* source)
{
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    return shader;
}

// ==========================================================
// Reset Ball
// ==========================================================
void resetBall()
{
    ballX = 0.0f;
    ballY = 0.0f;

    ballSpeedX *= -1.0f;
}

// ==========================================================
// Restart Game
// ==========================================================
void restartGame()
{
    leftScore = 0;
    rightScore = 0;

    gameOver = false;

    winnerText = "";

    leftPaddleY = 0.0f;
    rightPaddleY = 0.0f;

    resetBall();
}

// ==========================================================
// Update Window Title Scoreboard
// ==========================================================
void updateWindowTitle(GLFWwindow* window)
{
    string title;

    if (!gameOver)
    {
        title =
            "Pong  |  Left: " +
            to_string(leftScore) +
            "   Right: " +
            to_string(rightScore);
    }
    else
    {
        title =
            winnerText +
            " Wins!  |  ENTER = Restart  |  ESC = Exit";
    }

    glfwSetWindowTitle(window, title.c_str());
}

// ==========================================================
// Input
// ==========================================================
void processInput(GLFWwindow* window)
{
    // ESC = quit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Restart
    if (gameOver &&
        glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        restartGame();
    }

    // Stop movement if game ended
    if (gameOver)
        return;

    // Left paddle
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        leftPaddleY += paddleSpeed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        leftPaddleY -= paddleSpeed;

    // Right paddle
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rightPaddleY += paddleSpeed;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rightPaddleY -= paddleSpeed;

    // Clamp paddles
    float paddleHalfHeight =
        paddleHeight * 0.5f;

    if (leftPaddleY + paddleHalfHeight > 1.0f)
        leftPaddleY = 1.0f - paddleHalfHeight;

    if (leftPaddleY - paddleHalfHeight < -1.0f)
        leftPaddleY = -1.0f + paddleHalfHeight;

    if (rightPaddleY + paddleHalfHeight > 1.0f)
        rightPaddleY = 1.0f - paddleHalfHeight;

    if (rightPaddleY - paddleHalfHeight < -1.0f)
        rightPaddleY = -1.0f + paddleHalfHeight;
}

// ==========================================================
// Main
// ==========================================================
int main()
{
    GLFWwindow* window;

    // ======================================================
    // Initialize GLFW
    // ======================================================
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);

    // ======================================================
    // Create Window
    // ======================================================
    window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Pong",
        NULL,
        NULL
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // ======================================================
    // Initialize GLEW
    // ======================================================
    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW failed\n";

        return -1;
    }

    cout << "OpenGL Version: "
         << glGetString(GL_VERSION)
         << endl;

    // ======================================================
    // Rectangle vertices
    // ======================================================
    float vertices[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,

        -0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // ======================================================
    // VAO + VBO
    // ======================================================
    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // ======================================================
    // Shaders
    // ======================================================
    unsigned int vertexShader =
        createShader(GL_VERTEX_SHADER,
                     vertexShaderSource);

    unsigned int fragmentShader =
        createShader(GL_FRAGMENT_SHADER,
                     fragmentShaderSource);

    unsigned int shaderProgram =
        glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);

    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);

    // ======================================================
    // Uniforms
    // ======================================================
    int offsetLoc =
        glGetUniformLocation(shaderProgram,
                             "offset");

    int scaleLoc =
        glGetUniformLocation(shaderProgram,
                             "scale");

    int colorLoc =
        glGetUniformLocation(shaderProgram,
                             "color");

    // ======================================================
    // Main Loop
    // ======================================================
    while (!glfwWindowShouldClose(window))
    {
        // ==================================================
        // Input
        // ==================================================
        processInput(window);

        updateWindowTitle(window);

        // ==================================================
        // Only update gameplay if not game over
        // ==================================================
        if (!gameOver)
        {
            float paddleHalfWidth =
                paddleWidth * 0.5f;

            float paddleHalfHeight =
                paddleHeight * 0.5f;

            float ballHalfSize =
                ballSize * 0.5f;

            // ==============================================
            // Move ball
            // ==============================================
            ballX += ballSpeedX;

            ballY += ballSpeedY;

            // ==============================================
            // Top collision
            // ==============================================
            if (ballY + ballHalfSize > 1.0f)
            {
                ballY = 1.0f - ballHalfSize;

                ballSpeedY *= -1.0f;
            }

            // ==============================================
            // Bottom collision
            // ==============================================
            if (ballY - ballHalfSize < -1.0f)
            {
                ballY = -1.0f + ballHalfSize;

                ballSpeedY *= -1.0f;
            }

            // ==============================================
            // LEFT paddle collision
            // ==============================================
            bool collisionLeft =

                ballX - ballHalfSize <
                    leftPaddleX + paddleHalfWidth &&

                ballX + ballHalfSize >
                    leftPaddleX - paddleHalfWidth &&

                ballY - ballHalfSize <
                    leftPaddleY + paddleHalfHeight &&

                ballY + ballHalfSize >
                    leftPaddleY - paddleHalfHeight;

            if (collisionLeft && ballSpeedX < 0.0f)
            {
                ballSpeedX *= -1.0f;

                ballX =
                    leftPaddleX +
                    paddleHalfWidth +
                    ballHalfSize;
            }

            // ==============================================
            // RIGHT paddle collision
            // ==============================================
            bool collisionRight =

                ballX + ballHalfSize >
                    rightPaddleX - paddleHalfWidth &&

                ballX - ballHalfSize <
                    rightPaddleX + paddleHalfWidth &&

                ballY - ballHalfSize <
                    rightPaddleY + paddleHalfHeight &&

                ballY + ballHalfSize >
                    rightPaddleY - paddleHalfHeight;

            if (collisionRight && ballSpeedX > 0.0f)
            {
                ballSpeedX *= -1.0f;

                ballX =
                    rightPaddleX -
                    paddleHalfWidth -
                    ballHalfSize;
            }

            // ==============================================
            // LEFT scores
            // ==============================================
            if (ballX > 1.1f)
            {
                leftScore++;

                resetBall();
            }

            // ==============================================
            // RIGHT scores
            // ==============================================
            if (ballX < -1.1f)
            {
                rightScore++;

                resetBall();
            }

            // ==============================================
            // Win check
            // ==============================================
            if (leftScore >= 10)
            {
                gameOver = true;

                winnerText = "LEFT PLAYER";
            }

            if (rightScore >= 10)
            {
                gameOver = true;

                winnerText = "RIGHT PLAYER";
            }
        }

        // ==================================================
        // Clear screen
        // ==================================================
        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        // ==================================================
        // Use shader
        // ==================================================
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        // ==================================================
        // Draw LEFT paddle
        // ==================================================
        glUniform2f(
            offsetLoc,
            leftPaddleX,
            leftPaddleY
        );

        glUniform2f(
            scaleLoc,
            paddleWidth,
            paddleHeight
        );

        glUniform3f(
            colorLoc,
            1.0f,
            1.0f,
            1.0f
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ==================================================
        // Draw RIGHT paddle
        // ==================================================
        glUniform2f(
            offsetLoc,
            rightPaddleX,
            rightPaddleY
        );

        glUniform2f(
            scaleLoc,
            paddleWidth,
            paddleHeight
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ==================================================
        // Draw BALL
        // ==================================================
        glUniform2f(
            offsetLoc,
            ballX,
            ballY
        );

        glUniform2f(
            scaleLoc,
            ballSize,
            ballSize
        );

        glUniform3f(
            colorLoc,
            1.0f,
            0.2f,
            0.2f
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ==================================================
        // Swap buffers
        // ==================================================
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // ======================================================
    // Cleanup
    // ======================================================
    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}