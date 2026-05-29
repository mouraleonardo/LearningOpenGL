#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "Mesh.h"

/*
    Renderer Class

    Responsible for rendering objects on the screen.

    This class connects a Shader object and a Mesh object
    and applies transformations before drawing.

    Responsibilities:

    - Activate the shader program
    - Apply transformations
    - Send matrices to the GPU
    - Render the mesh
*/
class Renderer
{
private:

    // Pointer to the shader used for rendering.
    // The shader controls how vertices and
    // fragments are processed by the GPU.
    Shader* shader;

    // Pointer to the mesh that will be rendered.
    // The mesh contains the vertex and index data.
    Mesh* mesh;

public:

    /*
        Constructor

        Receives references to a Shader and Mesh
        object and stores them for rendering.
    */
    Renderer(
        Shader* shader,
        Mesh* mesh);

    /*
        Render Function

        Renders the mesh using the assigned shader.

        Parameters:
            angle - Rotation angle in radians.

        In this project, the angle is used to rotate
        the 3D cube continuously around the Y axis.
    */
    void Render(float angle);
};

#endif