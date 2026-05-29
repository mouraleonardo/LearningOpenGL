#version 330 core

/*
    Vertex Position Attribute

    Receives the position of each vertex
    from the Vertex Buffer Object (VBO).

    Layout Location 0 corresponds to the
    position data configured in Mesh.cpp.

    Components:
    X, Y, Z
*/
layout(location = 0) in vec3 aPos;

/*
    Vertex Color Attribute

    Receives the RGB color associated
    with each vertex.

    Layout Location 1 corresponds to the
    color data configured in Mesh.cpp.

    Components:
    R, G, B
*/
layout(location = 1) in vec3 aColor;

/*
    Model-View-Projection Matrix

    Sent from the CPU application through
    the Renderer class.

    This matrix combines:

    - Model Transformation
    - View Transformation
    - Projection Transformation

    MVP = Projection × View × Model
*/
uniform mat4 mvp;

/*
    Output Color

    Passes the vertex color to the
    Fragment Shader.

    During rasterization, OpenGL
    automatically interpolates the
    colors between vertices.
*/
out vec3 vertexColor;

/*
    Vertex Shader Main Function

    Executes once for every vertex.

    Responsibilities:

    1. Transform the vertex position
       from local space to clip space.

    2. Pass the vertex color to the
       Fragment Shader.
*/
void main()
{
    /*
        Transform the vertex position
        using the MVP matrix.

        The resulting position is stored
        in gl_Position, which OpenGL uses
        to determine where the vertex
        appears on the screen.
    */
    gl_Position =
        mvp *
        vec4(aPos, 1.0);

    /*
        Pass the vertex color to the
        Fragment Shader.
    */
    vertexColor = aColor;
}