#ifndef SHADER_H
#define SHADER_H

/*
    Shader Class

    Responsible for loading, compiling,
    and managing OpenGL shader programs.

    A shader program consists of:

    - Vertex Shader
        Processes vertex data and applies
        transformations such as translation,
        rotation, and projection.

    - Fragment Shader
        Determines the final color of each
        pixel rendered on the screen.

    This class loads shader source code
    from external GLSL files, compiles them,
    links them into a shader program, and
    provides access to the program during
    rendering.
*/
class Shader
{
private:

    // OpenGL shader program identifier.
    // Stores the linked vertex and fragment
    // shaders used by the GPU.
    unsigned int programID;

public:

    /*
        Constructor

        Loads shader source code from files,
        compiles the vertex and fragment shaders,
        and links them into a shader program.

        Parameters:

        vertexPath
            Path to the vertex shader file.

        fragmentPath
            Path to the fragment shader file.
    */
    Shader(
        const char* vertexPath,
        const char* fragmentPath);

    /*
        Use Function

        Activates this shader program so it
        becomes the current program used for
        rendering.
    */
    void Use();

    /*
        GetID Function

        Returns the OpenGL shader program ID.

        This ID is commonly used to access
        uniforms and other shader-related
        resources.

        Returns:
            OpenGL program identifier.
    */
    unsigned int GetID() const;
};

#endif