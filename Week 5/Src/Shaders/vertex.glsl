/*
    ============================================================
    Vertex Shader
    File: vertex.glsl

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    This shader processes every vertex before it is drawn
    on the screen. It receives position and color data from
    the CPU, applies transformations using the MVP matrix,
    and passes information to the fragment shader.

    Concepts Demonstrated:
        • Vertex Processing
        • Translation
        • Rotation
        • Scaling
        • Matrix Transformations
        • Vertex Attributes
        • Uniform Variables
        • Interpolated Outputs

    Input Attributes:
        aPos
            Position of a vertex (x, y, z)

        aColor
            Color of a vertex (r, g, b)

    Uniforms:
        mvp
            Model-View-Projection matrix used to transform
            vertices from object space into clip space.

            MVP = Projection × View × Model

            Model:
                Positions, rotates, and scales an object

            View:
                Represents the camera transformation

            Projection:
                Defines the visible world area

    Outputs Sent to Fragment Shader:
        vertexColor
            Passes vertex color information

        vertexHeight
            Stores the original Y coordinate of the vertex

        worldX
            Stores the original X coordinate of the vertex

    Main Operations:
        1. Transform vertex position using the MVP matrix
        2. Store the transformed position in gl_Position
        3. Pass color information forward
        4. Pass X and Y coordinate information forward

    Graphics Pipeline:

        Vertex Data
             ↓
        Vertex Shader  ← This File
             ↓
        Rasterizer
             ↓
        Fragment Shader
             ↓
        Screen

    Notes:
        gl_Position is a built-in output variable required
        by every vertex shader. It contains the final
        transformed position of the vertex.

        Values passed through "out" variables are
        automatically interpolated across the triangle
        before reaching the fragment shader.
    ============================================================
*/

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 mvp;

out vec3 vertexColor;
out float vertexHeight;
out float worldX;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);

    vertexColor = aColor;

    vertexHeight = aPos.y;
    worldX = aPos.x;
}