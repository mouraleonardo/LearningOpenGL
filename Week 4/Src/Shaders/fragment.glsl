#version 330 core

/*
    Input Color

    Receives the interpolated color from
    the Vertex Shader.

    OpenGL automatically interpolates the
    vertex colors across the surface of
    each triangle.
*/
in vec3 vertexColor;

/*
    Fragment Output

    Stores the final color that will be
    written to the framebuffer for the
    current pixel.
*/
out vec4 FragColor;

/*
    Fragment Shader Main Function

    Executes once for every fragment
    (potential pixel) generated during
    rasterization.

    The RGB color received from the
    Vertex Shader is combined with an
    alpha value of 1.0 (fully opaque)
    and assigned as the final pixel color.
*/
void main()
{
    FragColor =
        vec4(
            vertexColor,
            1.0);
}