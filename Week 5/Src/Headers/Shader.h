/*
    ============================================================
    Shader.h

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    Defines the Shader class used to load,
    compile, link, and manage OpenGL shader
    programs.

    Shaders are small programs that execute
    directly on the GPU and control how objects
    are rendered on the screen.

    In this project, the shader system is
    responsible for:

        • Transforming vertices
        • Applying colors
        • Creating visual effects
        • Rendering animated graphics

    OpenGL Shader Pipeline:

        Vertex Data
              ↓
        Vertex Shader
              ↓
        Rasterizer
              ↓
        Fragment Shader
              ↓
        Final Pixels

    Shader Types Used:

        Vertex Shader

            Processes each vertex.

            Responsible for:

                • Translation
                • Rotation
                • Scaling
                • Projection

            Produces the final position of
            vertices on the screen.

        Fragment Shader

            Processes each fragment (pixel).

            Responsible for:

                • Color calculations
                • Lighting effects
                • Gradients
                • Reflections
                • Visual appearance

    Shader Program Creation Process:

        1. Load shader source files
        2. Compile vertex shader
        3. Compile fragment shader
        4. Link shaders together
        5. Create shader program
        6. Use program during rendering

    Files Used:

        vertex.glsl
            Contains vertex shader code.

        fragment.glsl
            Contains fragment shader code.

    Main Functions:

        Shader(...)
            Loads and creates shader program.

        Use()
            Activates the shader.

        GetID()
            Returns OpenGL program ID.

    ============================================================
*/

#ifndef SHADER_H
#define SHADER_H

/*
    Shader Class

    Encapsulates an OpenGL shader program.

    Handles loading, compilation,
    linking, and activation of shaders.
*/
class Shader
{
private:

    /*
        OpenGL Program ID

        Unique identifier assigned by OpenGL
        to the linked shader program.

        Contains:

            • Compiled Vertex Shader
            • Compiled Fragment Shader

        Used whenever rendering occurs.
    */
    unsigned int programID;

public:

    /*
        Constructor

        Creates a complete shader program.

        Responsibilities:

            • Read GLSL source files
            • Compile vertex shader
            • Compile fragment shader
            • Link shaders into a program
            • Store program ID

        Parameters:

            vertexPath

                Path to vertex shader file.

                Example:
                    "vertex.glsl"

            fragmentPath

                Path to fragment shader file.

                Example:
                    "fragment.glsl"
    */
    Shader(
        const char* vertexPath,
        const char* fragmentPath);

    /*
        Use Function

        Makes this shader program the
        currently active program.

        Any objects rendered afterward
        will use this shader until another
        shader is activated.

        Internally calls:

            glUseProgram(programID)
    */
    void Use();

    /*
        GetID Function

        Returns the OpenGL program ID.

        Useful when accessing uniforms.

        Example Uniforms:

            MVP Matrix
            Time
            Colors
            Lighting Values

        Returns:

            Unsigned integer representing
            the OpenGL shader program.
    */
    unsigned int GetID() const;
};

#endif