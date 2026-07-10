/*
    ============================================================
    Shader - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This file implements the Shader class responsible for
    loading, compiling, linking, and managing GLSL shader
    programs.

    A Shader Program consists of multiple shader stages that
    execute on the GPU. In this project, two stages are used:

        • Vertex Shader
        • Fragment Shader

    The Shader class automates the complete shader creation
    process, including:

        • Reading GLSL source files
        • Compiling shader stages
        • Linking the shader program
        • Error checking
        • Activating the program
        • Sending uniform variables to the GPU

    Responsibilities:

        • Load shader source code
        • Compile GLSL shaders
        • Link shader programs
        • Report compilation errors
        • Activate shader programs
        • Upload uniform values

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLSL
        • GLEW
        • GLM
        • C++

    Learning Topics:

        • Shader Programming
        • Vertex Shader
        • Fragment Shader
        • Shader Compilation
        • Program Linking
        • Uniform Variables
        • GPU Programming
        • GLSL

    ============================================================
*/

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(
    const char* vertexPath,
    const char* fragmentPath)
{
    //----------------------------------------------------------
    // Read the shader source files.
    //----------------------------------------------------------

    std::string vertexCode =
        ReadFile(vertexPath);

    std::string fragmentCode =
        ReadFile(fragmentPath);

    //----------------------------------------------------------
    // Compile both shader stages.
    //----------------------------------------------------------

    GLuint vertexShader =
        Compile(
            GL_VERTEX_SHADER,
            vertexCode
        );

    GLuint fragmentShader =
        Compile(
            GL_FRAGMENT_SHADER,
            fragmentCode
        );

    //----------------------------------------------------------
    // Create the Shader Program.
    //----------------------------------------------------------

    ID = glCreateProgram();

    //----------------------------------------------------------
    // Attach both compiled shaders.
    //----------------------------------------------------------

    glAttachShader(
        ID,
        vertexShader
    );

    glAttachShader(
        ID,
        fragmentShader
    );

    //----------------------------------------------------------
    // Link the Shader Program.
    //----------------------------------------------------------

    glLinkProgram(ID);

    //----------------------------------------------------------
    // Verify if linking succeeded.
    //----------------------------------------------------------

    CheckProgram(ID);

    //----------------------------------------------------------
    // Individual shaders are no longer needed after linking.
    //----------------------------------------------------------

    glDeleteShader(vertexShader);

    glDeleteShader(fragmentShader);
}

std::string Shader::ReadFile(const char* path)
{
    //----------------------------------------------------------
    // Open the shader source file.
    //----------------------------------------------------------

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout
            << "Failed to open shader file: "
            << path
            << std::endl;

        return "";
    }

    //----------------------------------------------------------
    // Read the entire file into memory.
    //----------------------------------------------------------

    std::stringstream stream;

    stream << file.rdbuf();

    file.close();

    return stream.str();
}

GLuint Shader::Compile(
    GLenum type,
    const std::string& source)
{
    //----------------------------------------------------------
    // Create a shader object.
    //----------------------------------------------------------

    GLuint shader =
        glCreateShader(type);

    const char* code =
        source.c_str();

    //----------------------------------------------------------
    // Upload the GLSL source code.
    //----------------------------------------------------------

    glShaderSource(
        shader,
        1,
        &code,
        nullptr
    );

    //----------------------------------------------------------
    // Compile the shader.
    //----------------------------------------------------------

    glCompileShader(shader);

    //----------------------------------------------------------
    // Verify compilation.
    //----------------------------------------------------------

    GLint success;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            shader,
            512,
            nullptr,
            infoLog
        );

        std::cout
            << "Shader compilation failed:"
            << std::endl;

        std::cout
            << infoLog
            << std::endl;
    }

    return shader;
}

void Shader::CheckProgram(GLuint program)
{
    //----------------------------------------------------------
    // Verify the shader program linking.
    //----------------------------------------------------------

    GLint success;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            program,
            512,
            nullptr,
            infoLog
        );

        std::cout
            << "Shader program linking failed:"
            << std::endl;

        std::cout
            << infoLog
            << std::endl;
    }
}

void Shader::Use() const
{
    //----------------------------------------------------------
    // Activate this shader program.
    //----------------------------------------------------------

    glUseProgram(ID);
}

void Shader::SetBool(
    const std::string& name,
    bool value) const
{
    //----------------------------------------------------------
    // Upload a boolean uniform.
    //----------------------------------------------------------

    glUniform1i(
        glGetUniformLocation(
            ID,
            name.c_str()
        ),
        (int)value
    );
}

void Shader::SetInt(
    const std::string& name,
    int value) const
{
    //----------------------------------------------------------
    // Upload an integer uniform.
    //----------------------------------------------------------

    glUniform1i(
        glGetUniformLocation(
            ID,
            name.c_str()
        ),
        value
    );
}

void Shader::SetFloat(
    const std::string& name,
    float value) const
{
    //----------------------------------------------------------
    // Upload a floating-point uniform.
    //----------------------------------------------------------

    glUniform1f(
        glGetUniformLocation(
            ID,
            name.c_str()
        ),
        value
    );
}

void Shader::SetVec3(
    const std::string& name,
    const glm::vec3& value) const
{
    //----------------------------------------------------------
    // Upload a vec3 uniform.
    //----------------------------------------------------------

    glUniform3fv(
        glGetUniformLocation(
            ID,
            name.c_str()
        ),
        1,
        &value[0]
    );
}

void Shader::SetMat4(
    const std::string& name,
    const glm::mat4& value) const
{
    //----------------------------------------------------------
    // Upload a 4x4 transformation matrix.
    //----------------------------------------------------------

    glUniformMatrix4fv(
        glGetUniformLocation(
            ID,
            name.c_str()
        ),
        1,
        GL_FALSE,
        &value[0][0]
    );
}