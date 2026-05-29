#include "Shader.h"

#include <glew.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

/*
    Constructor

    Loads, compiles, and links the vertex
    and fragment shaders into an OpenGL
    shader program.

    Parameters:

    vertexPath
        Path to the vertex shader file.

    fragmentPath
        Path to the fragment shader file.
*/
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    /*
        Open the shader source files.
    */
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);

    /*
        Verify that the shader files
        were successfully opened.

        If a file cannot be found,
        an error message is displayed.
    */
    if (!vertexFile.is_open())
    {
        std::cout
            << "ERROR: Vertex shader not found: "
            << vertexPath
            << std::endl;
    }

    if (!fragmentFile.is_open())
    {
        std::cout
            << "ERROR: Fragment shader not found: "
            << fragmentPath
            << std::endl;
    }

    /*
        Read the contents of the shader
        files into string streams.
    */
    std::stringstream vertexStream;
    std::stringstream fragmentStream;

    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    /*
        Convert shader source code
        into standard strings.
    */
    std::string vertexCode = vertexStream.str();
    std::string fragmentCode = fragmentStream.str();

    /*
        Convert strings into C-style
        character arrays required by
        OpenGL functions.
    */
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    /*
        Create and compile the
        Vertex Shader.

        The vertex shader processes
        vertex data and applies
        transformations such as
        rotation, translation,
        and projection.
    */
    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexSource,
        nullptr);

    glCompileShader(vertexShader);

    /*
        Create and compile the
        Fragment Shader.

        The fragment shader determines
        the final color of each pixel
        rendered on the screen.
    */
    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentSource,
        nullptr);

    glCompileShader(fragmentShader);

    /*
        Create the OpenGL shader program.

        A shader program combines the
        vertex and fragment shaders into
        a single executable GPU program.
    */
    programID = glCreateProgram();

    /*
        Attach compiled shaders to
        the shader program.
    */
    glAttachShader(
        programID,
        vertexShader);

    glAttachShader(
        programID,
        fragmentShader);

    /*
        Link the shader program.

        After linking, OpenGL can use
        the program for rendering.
    */
    glLinkProgram(programID);

    /*
        Delete individual shader objects.

        Once linked, the program contains
        all required shader information,
        so the separate shader objects are
        no longer needed.
    */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

/*
    Use Function

    Activates the shader program,
    making it the current program
    used for rendering.
*/
void Shader::Use()
{
    glUseProgram(programID);
}

/*
    GetID Function

    Returns the OpenGL shader
    program identifier.

    This ID can be used to access
    uniforms and other shader-related
    resources.
*/
unsigned int Shader::GetID() const
{
    return programID;
}