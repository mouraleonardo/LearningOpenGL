/*
    ============================================================
    Mesh.h

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    Defines the Mesh class used to store and render
    geometry in OpenGL.

    A Mesh represents a collection of vertices that
    form a drawable object.

    Examples in this project:

        • Car Body
        • Wheels
        • Wheel Rims
        • Smoke Particles

    Responsibilities:
        • Store OpenGL buffer IDs
        • Upload vertex data to the GPU
        • Render geometry
        • Manage GPU resources

    OpenGL Objects Used:

        VAO (Vertex Array Object)
            Stores vertex attribute configuration.

        VBO (Vertex Buffer Object)
            Stores vertex data in GPU memory.

    Vertex Format:

        Each vertex contains:

            x, y, z,
            r, g, b

        Position:
            3 floats

        Color:
            3 floats

        Total:
            6 floats per vertex

    Example Vertex:

        1.0f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f

        Position:
            (1.0, 0.5, 0.0)

        Color:
            Red

    Class Workflow:

        Vertex Data
              ↓
        Mesh Constructor
              ↓
        Create VAO/VBO
              ↓
        Upload Data to GPU
              ↓
        Draw()
              ↓
        Rendered Object

    Main Functions:

        Mesh(...)
            Creates buffers and uploads
            geometry to the GPU.

        Draw()
            Renders the mesh.

        ~Mesh()
            Releases GPU resources.

    ============================================================
*/

#ifndef MESH_H
#define MESH_H

// Provides the std::vector container used
// to store vertex data.
#include <vector>

/*
    Mesh Class

    Encapsulates all geometry data required
    to render an object in OpenGL.
*/
class Mesh
{
private:

    /*
        Vertex Array Object (VAO)

        Stores:

            • Vertex attribute layouts
            • Buffer bindings
            • Attribute configurations

        The VAO remembers how vertex data
        should be interpreted by OpenGL.
    */
    unsigned int VAO;

    /*
        Vertex Buffer Object (VBO)

        Stores actual vertex data
        in GPU memory.
    */
    unsigned int VBO;

    /*
        Total number of vertices
        contained in the mesh.

        Used by glDrawArrays()
        when rendering.
    */
    unsigned int vertexCount;

public:

    /*
        Constructor

        Receives vertex data and:

            • Creates OpenGL buffers
            • Uploads data to GPU memory
            • Configures vertex attributes

        Parameter:

            vertices

                Collection of floats
                representing vertex data.

                Format:

                    x y z r g b
    */
    Mesh(
        const std::vector<float>& vertices);

    /*
        Draw Function

        Renders the mesh using
        the currently active shader.

        Internally:

            • Binds VAO
            • Calls glDrawArrays()
            • Unbinds VAO
    */
    void Draw() const;

    /*
        Destructor

        Automatically releases:

            • VAO
            • VBO

        Prevents GPU memory leaks.
    */
    ~Mesh();
};

#endif