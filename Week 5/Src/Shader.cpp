/*
    ============================================================
    Shader.cpp

    Purpose:
    Loads shader source code from files, compiles the
    vertex and fragment shaders, links them into a
    shader program, and provides functions to activate
    the program for rendering.

    OpenGL Shader Pipeline:

        Vertex Shader
              ↓
        Fragment Shader
              ↓
        Shader Program
              ↓
        GPU Rendering

    Main Responsibilities:
        • Read GLSL files from disk
        • Compile shaders
        • Report compilation errors
        • Link shaders into a program
        • Activate the shader program

    ============================================================
*/

#include "Shader.h"

// OpenGL functions
#include <glew.h>

// File reading
#include <fstream>

// String stream for reading entire files
#include <sstream>

// Console output
#include <iostream>

// String class
#include <string>

/*
    Constructor

    vertexPath:
        Path to vertex shader source file

    fragmentPath:
        Path to fragment shader source file
*/
Shader::Shader(
    const char* vertexPath,
    const char* fragmentPath)
{
    /*
        Open shader source files.
    */
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);

    /*
        Verify vertex shader file opened successfully.
    */
    if (!vertexFile.is_open())
    {
        std::cout
            << "ERROR: Could not open vertex shader: "
            << vertexPath
            << std::endl;
    }

    /*
        Verify fragment shader file opened successfully.
    */
    if (!fragmentFile.is_open())
    {
        std::cout
            << "ERROR: Could not open fragment shader: "
            << fragmentPath
            << std::endl;
    }

    /*
        String streams will hold the entire
        contents of each shader file.
    */
    std::stringstream vertexStream;
    std::stringstream fragmentStream;

    /*
        Copy entire vertex shader file
        into the stream.
    */
    vertexStream
        << vertexFile.rdbuf();

    /*
        Copy entire fragment shader file
        into the stream.
    */
    fragmentStream
        << fragmentFile.rdbuf();

    /*
        Convert stream contents into strings.
    */
    std::string vertexCode =
        vertexStream.str();

    std::string fragmentCode =
        fragmentStream.str();

    /*
        Convert C++ strings into C-style strings.

        OpenGL requires const char* source code.
    */
    const char* vertexSource =
        vertexCode.c_str();

    const char* fragmentSource =
        fragmentCode.c_str();

    /*
        Variables used for error checking.
    */

    // Stores success/failure state
    GLint success;

    // Stores compiler/linker error messages
    GLchar infoLog[1024];

    /*
        =================================================
        VERTEX SHADER COMPILATION
        =================================================
    */

    /*
        Create an empty vertex shader object.
    */
    GLuint vertexShader =
        glCreateShader(
            GL_VERTEX_SHADER);

    /*
        Attach source code to shader object.

        Parameters:
            Shader ID
            Number of source strings
            Source code
            Length (nullptr = automatic)
    */
    glShaderSource(
        vertexShader,
        1,
        &vertexSource,
        nullptr);

    /*
        Compile GLSL source code into GPU instructions.
    */
    glCompileShader(
        vertexShader);

    /*
        Check whether compilation succeeded.
    */
    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success);

    /*
        Display compilation errors if compilation failed.
    */
    if (!success)
    {
        glGetShaderInfoLog(
            vertexShader,
            sizeof(infoLog),
            nullptr,
            infoLog);

        std::cout
            << "\nVERTEX SHADER COMPILATION ERROR\n"
            << infoLog
            << std::endl;
    }

    /*
        =================================================
        FRAGMENT SHADER COMPILATION
        =================================================
    */

    /*
        Create fragment shader object.
    */
    GLuint fragmentShader =
        glCreateShader(
            GL_FRAGMENT_SHADER);

    /*
        Attach source code.
    */
    glShaderSource(
        fragmentShader,
        1,
        &fragmentSource,
        nullptr);

    /*
        Compile fragment shader.
    */
    glCompileShader(
        fragmentShader);

    /*
        Check compilation status.
    */
    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success);

    /*
        Display errors if compilation failed.
    */
    if (!success)
    {
        glGetShaderInfoLog(
            fragmentShader,
            sizeof(infoLog),
            nullptr,
            infoLog);

        std::cout
            << "\nFRAGMENT SHADER COMPILATION ERROR\n"
            << infoLog
            << std::endl;
    }

    /*
        =================================================
        SHADER PROGRAM LINKING
        =================================================

        After both shaders compile successfully,
        they are combined into a single shader
        program that OpenGL can execute.
    */

    /*
        Create program object.
    */
    programID =
        glCreateProgram();

    /*
        Attach compiled vertex shader.
    */
    glAttachShader(
        programID,
        vertexShader);

    /*
        Attach compiled fragment shader.
    */
    glAttachShader(
        programID,
        fragmentShader);

    /*
        Link shaders together.

        This creates the final GPU program.
    */
    glLinkProgram(
        programID);

    /*
        Check link status.
    */
    glGetProgramiv(
        programID,
        GL_LINK_STATUS,
        &success);

    /*
        Print linker errors if linking failed.
    */
    if (!success)
    {
        glGetProgramInfoLog(
            programID,
            sizeof(infoLog),
            nullptr,
            infoLog);

        std::cout
            << "\nPROGRAM LINK ERROR\n"
            << infoLog
            << std::endl;
    }

    /*
        Once linked, the individual shader
        objects are no longer needed.

        The program now contains their compiled code.
    */
    glDeleteShader(
        vertexShader);

    glDeleteShader(
        fragmentShader);
}

/*
    Use()

    Makes this shader program the active
    program used for rendering.
*/
void Shader::Use()
{
    glUseProgram(
        programID);
}

/*
    GetID()

    Returns the OpenGL program ID.

    Used when setting uniforms such as:

        MVP matrices
        Time values
        Colors
*/
unsigned int Shader::GetID() const
{
    return programID;
}