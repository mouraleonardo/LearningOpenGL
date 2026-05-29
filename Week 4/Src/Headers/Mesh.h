#ifndef MESH_H
#define MESH_H

/*
    Mesh Class

    Responsible for managing the geometry of a 3D object.

    This class stores and manages:

    VAO (Vertex Array Object)
        Stores vertex attribute configuration.

    VBO (Vertex Buffer Object)
        Stores vertex data such as positions
        and colors in GPU memory.

    EBO (Element Buffer Object)
        Stores vertex indices, allowing
        vertices to be reused instead of
        duplicated.
*/

class Mesh
{
private:

    // Vertex Array Object
    // Keeps track of vertex attribute settings.
    unsigned int VAO;

    // Vertex Buffer Object
    // Stores vertex position and color data.
    unsigned int VBO;

    // Element Buffer Object
    // Stores indices used to draw triangles.
    unsigned int EBO;

public:

    /*
        Constructor

        Creates and initializes the VAO,
        VBO, and EBO.

        Uploads vertex and index data
        to the GPU.
    */
    Mesh();

    /*
        Draw Function

        Binds the VAO and renders the mesh
        using indexed drawing through
        the Element Buffer Object (EBO).
    */
    void Draw();

    /*
        Destructor

        Releases GPU resources when the
        Mesh object is destroyed.
    */
    ~Mesh();
};

#endif