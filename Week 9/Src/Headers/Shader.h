/*
    ============================================================
    Shader - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This class encapsulates an OpenGL Shader Program.

    A shader program is composed of multiple shader stages
    that execute directly on the GPU. In this project, the
    Shader class manages two stages:

        • Vertex Shader
        • Fragment Shader

    The class automates the complete shader workflow,
    including loading source files, compiling GLSL code,
    linking the shader program, activating the program,
    and uploading uniform variables.

    Responsibilities:

        • Load GLSL source files
        • Compile shader stages
        • Link the Shader Program
        • Activate the shader program
        • Upload uniform variables
        • Report compilation and linking errors

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
        • GLSL
        • Uniform Variables
        • GPU Programming
        • Shader Compilation
        • Program Linking

    ============================================================
*/

#pragma once

#include <string>

#include <glew.h>
#include <glm.hpp>

//
//--------------------------------------------------------------
// Shader
//--------------------------------------------------------------
//
// Represents an OpenGL Shader Program.
//
// This class hides all low-level OpenGL calls required to
// create, compile, link and use GLSL shaders.
//
class Shader
{
public:

    //----------------------------------------------------------
    // OpenGL Shader Program identifier.
    //
    // This handle uniquely identifies the program stored
    // inside GPU memory.
    //----------------------------------------------------------
    GLuint ID;

    //----------------------------------------------------------
    // Constructor.
    //
    // Loads the Vertex Shader and Fragment Shader source
    // files, compiles both shaders, links the Shader Program,
    // and validates the final result.
    //----------------------------------------------------------
    Shader(
        const char* vertexPath,
        const char* fragmentPath
    );

    //----------------------------------------------------------
    // Activates the Shader Program.
    //
    // After calling this function, every subsequent draw call
    // will use this shader until another program is activated.
    //----------------------------------------------------------
    void Use() const;

    //----------------------------------------------------------
    // Uploads a boolean uniform.
    //----------------------------------------------------------
    void SetBool(
        const std::string& name,
        bool value
    ) const;

    //----------------------------------------------------------
    // Uploads an integer uniform.
    //----------------------------------------------------------
    void SetInt(
        const std::string& name,
        int value
    ) const;

    //----------------------------------------------------------
    // Uploads a floating-point uniform.
    //----------------------------------------------------------
    void SetFloat(
        const std::string& name,
        float value
    ) const;

    //----------------------------------------------------------
    // Uploads a vec3 uniform.
    //
    // Commonly used for positions, colors, directions and
    // lighting parameters.
    //----------------------------------------------------------
    void SetVec3(
        const std::string& name,
        const glm::vec3& value
    ) const;

    //----------------------------------------------------------
    // Uploads a 4x4 matrix uniform.
    //
    // Usually used for:
    //
    //      • Model Matrix
    //      • View Matrix
    //      • Projection Matrix
    //----------------------------------------------------------
    void SetMat4(
        const std::string& name,
        const glm::mat4& value
    ) const;

private:

    //----------------------------------------------------------
    // Reads a GLSL source file from disk.
    //
    // Returns the complete file contents as a string.
    //----------------------------------------------------------
    std::string ReadFile(
        const char* path
    );

    //----------------------------------------------------------
    // Compiles a shader stage.
    //
    // Supported shader types include:
    //
    //      • GL_VERTEX_SHADER
    //      • GL_FRAGMENT_SHADER
    //----------------------------------------------------------
    GLuint Compile(
        GLenum type,
        const std::string& source
    );

    //----------------------------------------------------------
    // Verifies whether the Shader Program was linked
    // successfully.
    //
    // Any linking errors are printed to the console.
    //----------------------------------------------------------
    void CheckProgram(
        GLuint program
    );
};