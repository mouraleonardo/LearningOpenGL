/*
    ============================================================
    Vertex Shader - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This Vertex Shader is responsible for transforming the
    object's vertices from local space into clip space.

    Each vertex received from the application passes through
    three transformation stages:

        • Model Transformation
        • View Transformation
        • Projection Transformation

    The shader also forwards the texture coordinates to the
    Fragment Shader, where they will be interpolated across
    the rendered surface.

    Responsibilities:

        • Receive vertex attributes
        • Apply Model Matrix
        • Apply View Matrix
        • Apply Projection Matrix
        • Forward texture coordinates

    OpenGL Pipeline:

        Vertex Shader   ← This stage
              ↓
        Primitive Assembly
              ↓
        Rasterization
              ↓
        Fragment Shader
              ↓
        Framebuffer

    Learning Topics:

        • GLSL Vertex Shaders
        • Vertex Attributes
        • Coordinate Systems
        • Model Matrix
        • View Matrix
        • Projection Matrix
        • Clip Space
        • Texture Coordinates

    ============================================================
*/

#version 330 core

//--------------------------------------------------------------
// Vertex Position.
//
// Defines the local position of each vertex that composes
// the 3D object.
//--------------------------------------------------------------
layout(location = 0) in vec3 aPosition;

//--------------------------------------------------------------
// Vertex Normal.
//
// Used for lighting calculations.
//
// Although this shader does not currently perform lighting,
// the normal is already provided for future implementations.
//--------------------------------------------------------------
layout(location = 1) in vec3 aNormal;

//--------------------------------------------------------------
// Texture Coordinates (UV).
//
// Defines which region of the texture corresponds to each
// vertex.
//--------------------------------------------------------------
layout(location = 2) in vec2 aTexCoord;

//--------------------------------------------------------------
// Texture coordinates passed to the Fragment Shader.
//
// During rasterization, OpenGL automatically interpolates
// these coordinates for every generated fragment.
//--------------------------------------------------------------
out vec2 TexCoord;

//--------------------------------------------------------------
// Model Matrix.
//
// Transforms vertices from Local Space into World Space.
//--------------------------------------------------------------
uniform mat4 model;

//--------------------------------------------------------------
// View Matrix.
//
// Transforms vertices from World Space into View (Camera)
// Space.
//--------------------------------------------------------------
uniform mat4 view;

//--------------------------------------------------------------
// Projection Matrix.
//
// Projects the 3D scene into Clip Space using a perspective
// projection.
//--------------------------------------------------------------
uniform mat4 projection;

void main()
{
    //----------------------------------------------------------
    // Forward the texture coordinates to the Fragment Shader.
    //----------------------------------------------------------

    TexCoord = aTexCoord;

    //----------------------------------------------------------
    // Transform the vertex through the complete graphics
    // pipeline.
    //
    // Local Space
    //      ↓
    // World Space
    //      ↓
    // View Space
    //      ↓
    // Clip Space
    //----------------------------------------------------------

    gl_Position =
        projection *
        view *
        model *
        vec4(aPosition, 1.0);
}